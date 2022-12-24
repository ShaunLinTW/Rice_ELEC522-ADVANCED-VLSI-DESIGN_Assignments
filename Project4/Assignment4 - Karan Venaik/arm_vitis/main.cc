
//
// C++ Application - main.cc for addertree - this version called t_fixed
//
// For other applications, your project name will replace the t_fixed and T_fixed used below.
// The variables in your VitisHLS file, for example "a" will be part of a function name to write to
// the accelerator from the ARM core as "XT_fixed_Set_a" below. 
//
// This version is for VitisHLS design exported directly to IP Creator for Vivado
// This version assumes that the VitisHLS code uses the AXI pragma for I/O
// This version assumes that the ap_fixed data type is used for integer/fraction.
// This version uses ap_fixed<16,3, AP_RND, AP_SAT> for a 16 bit signed word with 3 integer bits.


// standard .h for c++ math and I/O
#include <cmath>
#include <iostream>


// .h file based on your original .hls design input
#include "t_fixed.h"

// .h file from export to IP Creator from VitisHLS. This file is in the repository added to Vitis
// It will be copied from the drivers folder to the local in my example at
// C:\ELEC522\cavallar\Tree_Fixed_HLS_Vitis\Vitis\design_1_wrapper\ps7_cortex9_0\standalone_ps7_c\include
#include "xt_fixed.h"

// Add the include path C:\Xilinx\Vitis_HLS\2021.1\include to Vitis project properties
// Add this, right click on the project name to access C/C++ Build Settings then C/C++ General
// Finally add path to Paths and Symbols, include directory
// For the c++ file for the fixed point data type
#include "ap_fixed.h"

// IMPORTANT HLS t_fixed HW instance - Needed pointer - see the xt_fixed.h file
XT_fixed T_fixed;

// The Board Support Package that Vitis builds when you start a project should have these files
// Memory map file from 
// C:\ELEC522\cavallar\Tree_Fixed_HLS_Vitis\Vitis\design_1_wrapper\ps7_cortexa9_0\standalone_ps7_cortexa9_0\bsp\ps7_cortexa9_0\include\

#include "xparameters.h"
// The Xilinx time function file for measuring ARM core cycles
#include "xtime_l.h"
// Xilinx function for interrupt controller - may not be used in polling example.
#include "xscugic.h"


// Used by C++ for the print command cout
using namespace std;


// Define our fixed point type used here to match the PL accelerator
typedef ap_fixed<16,3, AP_RND, AP_SAT> FIXED_TYPE;



// The AXI interface sends only "raw bits" so we need to convert standard data types we use to
// match the ap_fixed data type in the PL accelerator.
// Using C++ functions per - RJ Cunningham
int get_int_reinterpret(FIXED_TYPE x) {
	return *(reinterpret_cast<short *>(&x));
}

FIXED_TYPE get_fixed_reinterpret(int x) {
	return *(reinterpret_cast<FIXED_TYPE *>(&x));
}


// actual MAIN control program running on ARM processor PS
int main()
{
	cout << "--- Start of the Program ---" << endl;

	// values for simulation and testing using C++ format with ap_fixed
	FIXED_TYPE a_in = 1.2;
	FIXED_TYPE b_in = 0.0;
	FIXED_TYPE c_in = -1.0;
	FIXED_TYPE d_in = 1.2;
	FIXED_TYPE e_in = 0.0;
	FIXED_TYPE f_in = 0.0;
	FIXED_TYPE g_in = 0.0;
	FIXED_TYPE h_in = 0.0;
	FIXED_TYPE r_sw = 0.0;
	FIXED_TYPE r_hw = 0.0;

	// values for sending over AXI bus to programmable logic (PL)
	unsigned int a_u32, b_u32, c_u32, d_u32, e_u32, f_u32, g_u32, h_u32, r_out_u32;

	// Standard floating data type to print
	float r_out_d = 0.0;

	// Handshake variable from output of HLS PL block
	int done_out = 0;

	// Variables for timing and counts used for application cycle counts and timing
	unsigned long long tt;
	int tt_print;
	double tt_seconds, pl_time, ps_time, speedup;
	XTime start_time_co;
	XTime stop_time_co;


	// Need to reinterpret the 16 bit ap_fixed values into raw unsigned 32 bit value for AXI transfer
	a_u32 = get_int_reinterpret(a_in);
	b_u32 = get_int_reinterpret(b_in);
	c_u32 = get_int_reinterpret(c_in);
	d_u32 = get_int_reinterpret(d_in);
	e_u32 = get_int_reinterpret(e_in);
	f_u32 = get_int_reinterpret(f_in);
	g_u32 = get_int_reinterpret(g_in);
	h_u32 = get_int_reinterpret(h_in);
	
	
	// cout is c++ version of printf and needs the iostream.h and namespace std declared above
	cout << "Ap_fixed variables initialized for software sim, a=" << a_in << " b=" << b_in << " c=" << c_in << " d=" << d_in << " e=" << e_in << " f=" << f_in << " g=" << g_in << " h=" << h_in << endl;

	// Get the starting time in cycle counts
	XTime_GetTime(&start_time_co);

	// The "cout" print statements are commented out after debugging is complete to not affect
	// the cycle count of processor performance.

	//cout << "Start time marked." << endl;

	// IMPORTANT PART OF PS-PL AXI COMMUNICATION
	// Need to initialize the PL accelerator. Use the pointer to the device instance, here &T_fixed
	// Second parameter is the DeviceId which is usually zero 0 for a single AXI interface.
	// The function names of the Initialize, Set, and Get functions will be in the drivers folder
	// in the C:\ELEC522\cavallar\Tree_Fixed_HLS_Vitis\Vitis\design_1_wrapper\export\design_1_wrapper\hw\drivers\t_fixed_v1_0\src 
	// and the xt_fixed.h example here.
	XT_fixed_Initialize(&T_fixed, 0);

	// Real processing on PL accelerator starts here
	// Write all unsigned raw 32 bit values to PL accelerator, since a_u32 = a_int;
	XT_fixed_Set_a(&T_fixed, a_u32);
	XT_fixed_Set_b(&T_fixed, b_u32);
	XT_fixed_Set_c(&T_fixed, c_u32);
	XT_fixed_Set_d(&T_fixed, d_u32);
	XT_fixed_Set_e(&T_fixed, e_u32);
	XT_fixed_Set_f(&T_fixed, f_u32);
	XT_fixed_Set_g(&T_fixed, g_u32);
	XT_fixed_Set_h(&T_fixed, h_u32);


	// Trigger the accelerator to start
	 XT_fixed_Start(&T_fixed);

	// Polling loop to wait for PL to complete.
	// Note that r_out_u32 is the special ap_fixed raw data bits.
	// Note that done_out is a standard 32 bit integer and does not need reinterpretation.
	      do {
	    	 r_out_u32 = XT_fixed_Get_r(&T_fixed);
	    	 done_out = XT_fixed_Get_done(&T_fixed);
	      } while (!XT_fixed_IsReady(&T_fixed));
	      // cout << "Detected HLS peripheral complete. Result received." << endl;


	// Capture the stop time on the processor
	XTime_GetTime(&stop_time_co);

	// END OF EXECUTION ON FPGA PROGRAMMABLE LOGIC
	cout << "Done signal from hardware = " << done_out << endl;
	
	// Convert unsigned 32 bit value from programmable logic back to fixed point
	r_hw = get_fixed_reinterpret(r_out_u32);
	r_out_d = r_hw;
	cout << "Hardware result as r_out_d =" << r_out_d << ", r_hw=" << r_hw << ", r_out_u32 =" << r_out_u32 << endl;



	// Compute timing on PL hardware using the accelerator.
	tt = stop_time_co - start_time_co;
	tt_print = (unsigned) tt;
	cout << "Done, Total time steps for I/O writes and I/O reads for PL = " << tt_print << endl;
	tt_seconds = COUNTS_PER_SECOND;
	cout << "Cycle counts per second for ARM A9 core for PL add = " << tt_seconds << endl;
	pl_time = (float) tt_print / tt_seconds;
	cout << "Time in seconds for PL hardware add = times steps / COUNTS_PER_SECOND = " << pl_time << endl;


	// ARM SOFTWARE ONLY PORTION OF PROGRAM
	// Generate the expected result on the ARM core using the built-in adder
	// Add the elements into the software result r_sw; first reset r_sw
    r_sw = 0;
    // Get timing and do software simulation with ap_fixed data in c++
    XTime_GetTime(&start_time_co);
    r_sw = a_in + b_in + c_in + d_in + e_in + f_in + g_in + h_in;
    XTime_GetTime(&stop_time_co);
    cout << "Result after ARM software only calculation = " << r_sw << endl;

    // Compute timing on ARM PS hardware
    tt = stop_time_co - start_time_co;
    tt_print = (unsigned) tt;
    cout << "Done, Total time steps for PS internal (including ap_fixed emulation) = " << tt_print << endl;
    tt_seconds = COUNTS_PER_SECOND;
    cout << "Cycle counts per second for ARM A9 core for PS internal add = " << tt_seconds << endl;
    ps_time = (float) tt_print / tt_seconds;
    cout << "Time in seconds for PS ARM software internal add = times steps / COUNTS_PER_SECOND = " << ps_time << endl;


    // Compute Speedup when using the programmable logic accelerator
    speedup = ps_time / pl_time;
    cout << "Speedup of FPGA accelerator versus all software on ARM or PS/PL = " << speedup << endl;
    cout << "--- End of the Program ---" << endl;


	return 0;
}

