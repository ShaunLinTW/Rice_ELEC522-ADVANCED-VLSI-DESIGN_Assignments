#include <systemc>
#include <iostream>
#include <cstdlib>
#include <cstddef>
#include <stdint.h>
#include "SysCFileHandler.h"
#include "ap_int.h"
#include "ap_fixed.h"
#include <complex>
#include <stdbool.h>
#include "autopilot_cbe.h"
#include "hls_stream.h"
#include "hls_half.h"
#include "hls_signal_handler.h"

using namespace std;
using namespace sc_core;
using namespace sc_dt;

// wrapc file define:
#define AUTOTB_TVIN_select_r "../tv/cdatafile/c.cordic.autotvin_select_r.dat"
#define AUTOTB_TVOUT_select_r "../tv/cdatafile/c.cordic.autotvout_select_r.dat"
#define AUTOTB_TVIN_CS_I_T "../tv/cdatafile/c.cordic.autotvin_CS_I_T.dat"
#define AUTOTB_TVOUT_CS_I_T "../tv/cdatafile/c.cordic.autotvout_CS_I_T.dat"
#define AUTOTB_TVIN_IA_I_S "../tv/cdatafile/c.cordic.autotvin_IA_I_S.dat"
#define AUTOTB_TVOUT_IA_I_S "../tv/cdatafile/c.cordic.autotvout_IA_I_S.dat"
#define AUTOTB_TVIN_IA_I_C "../tv/cdatafile/c.cordic.autotvin_IA_I_C.dat"
#define AUTOTB_TVOUT_IA_I_C "../tv/cdatafile/c.cordic.autotvout_IA_I_C.dat"
#define AUTOTB_TVIN_CS_O_SIN "../tv/cdatafile/c.cordic.autotvin_CS_O_SIN.dat"
#define AUTOTB_TVOUT_CS_O_SIN "../tv/cdatafile/c.cordic.autotvout_CS_O_SIN.dat"
#define AUTOTB_TVIN_CS_O_COS "../tv/cdatafile/c.cordic.autotvin_CS_O_COS.dat"
#define AUTOTB_TVOUT_CS_O_COS "../tv/cdatafile/c.cordic.autotvout_CS_O_COS.dat"
#define AUTOTB_TVIN_IA_O_IAT "../tv/cdatafile/c.cordic.autotvin_IA_O_IAT.dat"
#define AUTOTB_TVOUT_IA_O_IAT "../tv/cdatafile/c.cordic.autotvout_IA_O_IAT.dat"
#define AUTOTB_TVIN_done "../tv/cdatafile/c.cordic.autotvin_done.dat"
#define AUTOTB_TVOUT_done "../tv/cdatafile/c.cordic.autotvout_done.dat"

#define INTER_TCL "../tv/cdatafile/ref.tcl"

// tvout file define:
#define AUTOTB_TVOUT_PC_select_r "../tv/rtldatafile/rtl.cordic.autotvout_select_r.dat"
#define AUTOTB_TVOUT_PC_CS_I_T "../tv/rtldatafile/rtl.cordic.autotvout_CS_I_T.dat"
#define AUTOTB_TVOUT_PC_IA_I_S "../tv/rtldatafile/rtl.cordic.autotvout_IA_I_S.dat"
#define AUTOTB_TVOUT_PC_IA_I_C "../tv/rtldatafile/rtl.cordic.autotvout_IA_I_C.dat"
#define AUTOTB_TVOUT_PC_CS_O_SIN "../tv/rtldatafile/rtl.cordic.autotvout_CS_O_SIN.dat"
#define AUTOTB_TVOUT_PC_CS_O_COS "../tv/rtldatafile/rtl.cordic.autotvout_CS_O_COS.dat"
#define AUTOTB_TVOUT_PC_IA_O_IAT "../tv/rtldatafile/rtl.cordic.autotvout_IA_O_IAT.dat"
#define AUTOTB_TVOUT_PC_done "../tv/rtldatafile/rtl.cordic.autotvout_done.dat"


static const bool little_endian()
{
  int a = 1;
  return *(char*)&a == 1;
}

inline static void rev_endian(char* p, size_t nbytes)
{
  std::reverse(p, p+nbytes);
}

template<size_t bit_width>
struct transaction {
  typedef uint64_t depth_t;
  static const size_t wbytes = (bit_width+7)>>3;
  static const size_t dbytes = sizeof(depth_t);
  const depth_t depth;
  const size_t vbytes;
  const size_t tbytes;
  char * const p;
  typedef char (*p_dat)[wbytes];
  p_dat vp;

  transaction(depth_t depth)
    : depth(depth), vbytes(wbytes*depth), tbytes(dbytes+vbytes),
      p(new char[tbytes]) {
    *(depth_t*)p = depth;
    rev_endian(p, dbytes);
    vp = (p_dat) (p+dbytes);
  }

  void reorder() {
    rev_endian(p, dbytes);
    p_dat vp = (p_dat) (p+dbytes);
    for (depth_t i = 0; i < depth; ++i) {
      rev_endian(vp[i], wbytes);
    }
  }

  template<size_t psize>
  void import(char* param, depth_t num, int64_t offset) {
    param -= offset*psize;
    for (depth_t i = 0; i < num; ++i) {
      memcpy(vp[i], param, wbytes);
      param += psize;
      if (little_endian()) {
        rev_endian(vp[i], wbytes);
      }
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[i], wbytes);
      param += psize;
    }
    vp += num;
  }

  template<size_t psize>
  void send(char* param, depth_t num, int64_t skip) {
    for (depth_t i = 0; i < num; ++i) {
      memcpy(param, vp[skip+i], wbytes);
      param += psize;
    }
  }

  ~transaction() { if (p) { delete[] p; } }
};


inline static const std::string begin_str(int num)
{
  return std::string("[[transaction]]           ")
         .append(std::to_string(num))
         .append("\n");
}

inline static const std::string end_str()
{
  return std::string("[[/transaction]]\n");
}

const std::string formatData(unsigned char *pos, size_t wbits)
{
  bool LE = little_endian();
  size_t wbytes = (wbits+7)>>3;
  size_t i = LE ? wbytes-1 : 0;
  auto next = [&] () {
    auto c = pos[i];
    LE ? --i : ++i;
    return c;
  };
  std::ostringstream ss;
  ss << "0x";
  if (int t = (wbits & 0x7)) {
    if (t <= 4) {
      unsigned char mask = (1<<t)-1;
      ss << std::hex << std::setfill('0') << std::setw(1)
         << (int) (next() & mask);
      wbytes -= 1;
    }
  }
  for (size_t i = 0; i < wbytes; ++i) {
    ss << std::hex << std::setfill('0') << std::setw(2) << (int)next();
  }
  ss.put('\n');
  return ss.str();
}

static bool RTLOutputCheckAndReplacement(std::string &data)
{
  bool changed = false;
  for (size_t i = 2; i < data.size(); ++i) {
    if (data[i] == 'X' || data[i] == 'x') {
      data[i] = '0';
      changed = true;
    }
  }
  return changed;
}

struct SimException : public std::exception {
  const char *msg;
  const size_t line;
  SimException(const char *msg, const size_t line)
    : msg(msg), line(line)
  {
  }
};

template<size_t bit_width>
class PostCheck
{
  static const char *bad;
  static const char *err;
  std::fstream stream;
  std::string s;

  void send(char *p, ap_uint<bit_width> &data, size_t l, size_t rest)
  {
    if (rest == 0) {
      if (!little_endian()) {
        const size_t wbytes = (bit_width+7)>>3;
        rev_endian(p-wbytes, wbytes);
      }
    } else if (rest < 8) {
      *p = data.range(l+rest-1, l).to_uint();
      send(p+1, data, l+rest, 0);
    } else {
      *p = data.range(l+8-1, l).to_uint();
      send(p+1, data, l+8, rest-8);
    }
  }

  void readline()
  {
    std::getline(stream, s);
    if (stream.eof()) {
      throw SimException(bad, __LINE__);
    }
  }

public:
  char *param;
  size_t psize;
  size_t depth;

  PostCheck(const char *file)
  {
    stream.open(file);
    if (stream.fail()) {
      throw SimException(err, __LINE__);
    } else {
      readline();
      if (s != "[[[runtime]]]") {
        throw SimException(bad, __LINE__);
      }
    }
  }

  ~PostCheck() noexcept(false)
  {
    stream.close();
  }

  void run(size_t AESL_transaction_pc, size_t skip)
  {
    if (stream.peek() == '[') {
      readline();
    }

    for (size_t i = 0; i < skip; ++i) {
      readline();
    }

    bool foundX = false;
    for (size_t i = 0; i < depth; ++i) {
      readline();
      foundX |= RTLOutputCheckAndReplacement(s);
      ap_uint<bit_width> data(s.c_str(), 16);
      send(param+i*psize, data, 0, bit_width);
    }
    if (foundX) {
      std::cerr << "WARNING: [SIM 212-201] RTL produces unknown value "
                << "'x' or 'X' on some port, possible cause: "
                << "There are uninitialized variables in the design.\n";
    }

    if (stream.peek() == '[') {
      readline();
    }
  }
};

template<size_t bit_width>
const char* PostCheck<bit_width>::bad = "Bad TV file";

template<size_t bit_width>
const char* PostCheck<bit_width>::err = "Error on TV file";
      
class INTER_TCL_FILE {
  public:
INTER_TCL_FILE(const char* name) {
  mName = name; 
  select_r_depth = 0;
  CS_I_T_depth = 0;
  IA_I_S_depth = 0;
  IA_I_C_depth = 0;
  CS_O_SIN_depth = 0;
  CS_O_COS_depth = 0;
  IA_O_IAT_depth = 0;
  done_depth = 0;
  trans_num =0;
}
~INTER_TCL_FILE() {
  mFile.open(mName);
  if (!mFile.good()) {
    cout << "Failed to open file ref.tcl" << endl;
    exit (1); 
  }
  string total_list = get_depth_list();
  mFile << "set depth_list {\n";
  mFile << total_list;
  mFile << "}\n";
  mFile << "set trans_num "<<trans_num<<endl;
  mFile.close();
}
string get_depth_list () {
  stringstream total_list;
  total_list << "{select_r " << select_r_depth << "}\n";
  total_list << "{CS_I_T " << CS_I_T_depth << "}\n";
  total_list << "{IA_I_S " << IA_I_S_depth << "}\n";
  total_list << "{IA_I_C " << IA_I_C_depth << "}\n";
  total_list << "{CS_O_SIN " << CS_O_SIN_depth << "}\n";
  total_list << "{CS_O_COS " << CS_O_COS_depth << "}\n";
  total_list << "{IA_O_IAT " << IA_O_IAT_depth << "}\n";
  total_list << "{done " << done_depth << "}\n";
  return total_list.str();
}
void set_num (int num , int* class_num) {
  (*class_num) = (*class_num) > num ? (*class_num) : num;
}
void set_string(std::string list, std::string* class_list) {
  (*class_list) = list;
}
  public:
    int select_r_depth;
    int CS_I_T_depth;
    int IA_I_S_depth;
    int IA_I_C_depth;
    int CS_O_SIN_depth;
    int CS_O_COS_depth;
    int IA_O_IAT_depth;
    int done_depth;
    int trans_num;
  private:
    ofstream mFile;
    const char* mName;
};


struct __cosim_s2__ { char data[2]; };
extern "C" void cordic_hw_stub_wrapper(char, __cosim_s2__*, __cosim_s2__*, __cosim_s2__*, volatile void *, volatile void *, volatile void *, volatile void *);

extern "C" void apatb_cordic_hw(char __xlx_apatb_param_select_r, __cosim_s2__* __xlx_apatb_param_CS_I_T, __cosim_s2__* __xlx_apatb_param_IA_I_S, __cosim_s2__* __xlx_apatb_param_IA_I_C, volatile void * __xlx_apatb_param_CS_O_SIN, volatile void * __xlx_apatb_param_CS_O_COS, volatile void * __xlx_apatb_param_IA_O_IAT, volatile void * __xlx_apatb_param_done) {
  refine_signal_handler();
  fstream wrapc_switch_file_token;
  wrapc_switch_file_token.open(".hls_cosim_wrapc_switch.log");
static AESL_FILE_HANDLER aesl_fh;
  int AESL_i;
  if (wrapc_switch_file_token.good())
  {

    CodeState = ENTER_WRAPC_PC;
    static unsigned AESL_transaction_pc = 0;
    string AESL_token;
    string AESL_num;
{
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_CS_O_SIN);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<16> > CS_O_SIN_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              CS_O_SIN_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "CS_O_SIN" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_CS_O_SIN)[0*2+0] = CS_O_SIN_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_CS_O_SIN)[0*2+1] = CS_O_SIN_pc_buffer[0].range(15, 8).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_CS_O_COS);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<16> > CS_O_COS_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              CS_O_COS_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "CS_O_COS" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_CS_O_COS)[0*2+0] = CS_O_COS_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_CS_O_COS)[0*2+1] = CS_O_COS_pc_buffer[0].range(15, 8).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_IA_O_IAT);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<16> > IA_O_IAT_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              IA_O_IAT_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "IA_O_IAT" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_IA_O_IAT)[0*2+0] = IA_O_IAT_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_IA_O_IAT)[0*2+1] = IA_O_IAT_pc_buffer[0].range(15, 8).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  {
      static ifstream rtl_tv_out_file;
      if (!rtl_tv_out_file.is_open()) {
        rtl_tv_out_file.open(AUTOTB_TVOUT_PC_done);
        if (rtl_tv_out_file.good()) {
          rtl_tv_out_file >> AESL_token;
          if (AESL_token != "[[[runtime]]]")
            exit(1);
        }
      }
  
      if (rtl_tv_out_file.good()) {
        rtl_tv_out_file >> AESL_token; 
        rtl_tv_out_file >> AESL_num;  // transaction number
        if (AESL_token != "[[transaction]]") {
          cerr << "Unexpected token: " << AESL_token << endl;
          exit(1);
        }
        if (atoi(AESL_num.c_str()) == AESL_transaction_pc) {
          std::vector<sc_bv<16> > done_pc_buffer(1);
          int i = 0;
          bool has_unknown_value = false;
          rtl_tv_out_file >> AESL_token; //data
          while (AESL_token != "[[/transaction]]"){

            has_unknown_value |= RTLOutputCheckAndReplacement(AESL_token);
  
            // push token into output port buffer
            if (AESL_token != "") {
              done_pc_buffer[i] = AESL_token.c_str();;
              i++;
            }
  
            rtl_tv_out_file >> AESL_token; //data or [[/transaction]]
            if (AESL_token == "[[[/runtime]]]" || rtl_tv_out_file.eof())
              exit(1);
          }
          if (has_unknown_value) {
            cerr << "WARNING: [SIM 212-201] RTL produces unknown value 'x' or 'X' on port " 
                 << "done" << ", possible cause: There are uninitialized variables in the C design."
                 << endl; 
          }
  
          if (i > 0) {((char*)__xlx_apatb_param_done)[0*2+0] = done_pc_buffer[0].range(7, 0).to_int64();
((char*)__xlx_apatb_param_done)[0*2+1] = done_pc_buffer[0].range(15, 8).to_int64();
}
        } // end transaction
      } // end file is good
    } // end post check logic bolck
  
    AESL_transaction_pc++;
    return ;
  }
static unsigned AESL_transaction;
static INTER_TCL_FILE tcl_file(INTER_TCL);
std::vector<char> __xlx_sprintf_buffer(1024);
CodeState = ENTER_WRAPC;
CodeState = DUMP_INPUTS;
// print select_r Transactions
{
aesl_fh.write(AUTOTB_TVIN_select_r, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)&__xlx_apatb_param_select_r;
aesl_fh.write(AUTOTB_TVIN_select_r, formatData(pos, 1));
}
  tcl_file.set_num(1, &tcl_file.select_r_depth);
aesl_fh.write(AUTOTB_TVIN_select_r, end_str());
}

// print CS_I_T Transactions
{
aesl_fh.write(AUTOTB_TVIN_CS_I_T, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_CS_I_T;
aesl_fh.write(AUTOTB_TVIN_CS_I_T, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.CS_I_T_depth);
aesl_fh.write(AUTOTB_TVIN_CS_I_T, end_str());
}

// print IA_I_S Transactions
{
aesl_fh.write(AUTOTB_TVIN_IA_I_S, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_IA_I_S;
aesl_fh.write(AUTOTB_TVIN_IA_I_S, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.IA_I_S_depth);
aesl_fh.write(AUTOTB_TVIN_IA_I_S, end_str());
}

// print IA_I_C Transactions
{
aesl_fh.write(AUTOTB_TVIN_IA_I_C, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_IA_I_C;
aesl_fh.write(AUTOTB_TVIN_IA_I_C, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.IA_I_C_depth);
aesl_fh.write(AUTOTB_TVIN_IA_I_C, end_str());
}

// print CS_O_SIN Transactions
{
aesl_fh.write(AUTOTB_TVIN_CS_O_SIN, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_CS_O_SIN;
aesl_fh.write(AUTOTB_TVIN_CS_O_SIN, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.CS_O_SIN_depth);
aesl_fh.write(AUTOTB_TVIN_CS_O_SIN, end_str());
}

// print CS_O_COS Transactions
{
aesl_fh.write(AUTOTB_TVIN_CS_O_COS, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_CS_O_COS;
aesl_fh.write(AUTOTB_TVIN_CS_O_COS, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.CS_O_COS_depth);
aesl_fh.write(AUTOTB_TVIN_CS_O_COS, end_str());
}

// print IA_O_IAT Transactions
{
aesl_fh.write(AUTOTB_TVIN_IA_O_IAT, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_IA_O_IAT;
aesl_fh.write(AUTOTB_TVIN_IA_O_IAT, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.IA_O_IAT_depth);
aesl_fh.write(AUTOTB_TVIN_IA_O_IAT, end_str());
}

// print done Transactions
{
aesl_fh.write(AUTOTB_TVIN_done, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_done;
aesl_fh.write(AUTOTB_TVIN_done, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.done_depth);
aesl_fh.write(AUTOTB_TVIN_done, end_str());
}

CodeState = CALL_C_DUT;
cordic_hw_stub_wrapper(__xlx_apatb_param_select_r, __xlx_apatb_param_CS_I_T, __xlx_apatb_param_IA_I_S, __xlx_apatb_param_IA_I_C, __xlx_apatb_param_CS_O_SIN, __xlx_apatb_param_CS_O_COS, __xlx_apatb_param_IA_O_IAT, __xlx_apatb_param_done);
CodeState = DUMP_OUTPUTS;
// print CS_O_SIN Transactions
{
aesl_fh.write(AUTOTB_TVOUT_CS_O_SIN, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_CS_O_SIN;
aesl_fh.write(AUTOTB_TVOUT_CS_O_SIN, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.CS_O_SIN_depth);
aesl_fh.write(AUTOTB_TVOUT_CS_O_SIN, end_str());
}

// print CS_O_COS Transactions
{
aesl_fh.write(AUTOTB_TVOUT_CS_O_COS, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_CS_O_COS;
aesl_fh.write(AUTOTB_TVOUT_CS_O_COS, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.CS_O_COS_depth);
aesl_fh.write(AUTOTB_TVOUT_CS_O_COS, end_str());
}

// print IA_O_IAT Transactions
{
aesl_fh.write(AUTOTB_TVOUT_IA_O_IAT, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_IA_O_IAT;
aesl_fh.write(AUTOTB_TVOUT_IA_O_IAT, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.IA_O_IAT_depth);
aesl_fh.write(AUTOTB_TVOUT_IA_O_IAT, end_str());
}

// print done Transactions
{
aesl_fh.write(AUTOTB_TVOUT_done, begin_str(AESL_transaction));
{
auto *pos = (unsigned char*)__xlx_apatb_param_done;
aesl_fh.write(AUTOTB_TVOUT_done, formatData(pos, 16));
}
  tcl_file.set_num(1, &tcl_file.done_depth);
aesl_fh.write(AUTOTB_TVOUT_done, end_str());
}

CodeState = DELETE_CHAR_BUFFERS;
AESL_transaction++;
tcl_file.set_num(AESL_transaction , &tcl_file.trans_num);
}
