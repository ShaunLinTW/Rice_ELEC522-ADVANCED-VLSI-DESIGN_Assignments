
//
// C++ Application - main.cc for addertree - this version called t_fixed
//
// For other applications, your project name will replace the t_fixed and Cordic used below.
// The variables in your VitisHLS file, for example "a" will be part of a function name to write to
// the accelerator from the ARM core as "XCordic_Set_a" below.
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
#include "xcordic.h"

// Add the include path C:\Xilinx\Vitis_HLS\2021.1\include to Vitis project properties
// Add this, right click on the project name to access C/C++ Build Settings then C/C++ General
// Finally add path to Paths and Symbols, include directory
// For the c++ file for the fixed point data type
#include "ap_fixed.h"

// IMPORTANT HLS t_fixed HW instance - Needed pointer - see the xt_fixed.h file
XCordic Cordic;

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
typedef ap_fixed<16,2> FIXED_TYPE;



// The AXI interface sends only "raw bits" so we need to convert standard data types we use to
// match the ap_fixed data type in the PL accelerator.
// Using C++ functions per - RJ Cunningham
int get_int_reinterpret(FIXED_TYPE x) {
	return *(reinterpret_cast<short *>(&x));
}

FIXED_TYPE get_fixed_reinterpret(int x) {
	return *(reinterpret_cast<FIXED_TYPE *>(&x));
}
#define PI 3.1415926

// actual MAIN control program running on ARM processor PS
int main()
{
	cout << "--- Start of the Program ---" << endl;

	// values for simulation and testing using C++ format with ap_fixed
	FIXED_TYPE mode_in = 1;
	FIXED_TYPE t_in = (FIXDT) (30.0 * PI / 180 );
	FIXED_TYPE ts_in = 0.886025;
	FIXED_TYPE tc_in = 0.5;


	// values for sending over AXI bus to programmable logic (PL)
	unsigned int mode_in_u32, t_in_u32, ts_in_u32, tc_in_u32;
	unsigned int CS_O_SIN_u32, CS_O_COS_u32, IA_O_IAT_u32;
	int done_out = 0;
	FIXDT CS_O_COS, CS_O_SIN, IA_O_IAT;


	// Need to reinterpret the 16 bit ap_fixed values into raw unsigned 32 bit value for AXI transfer
	mode_in_u32 = 0;
	t_in_u32 = get_int_reinterpret(t_in);
	ts_in_u32 = get_int_reinterpret(ts_in);
	tc_in_u32 = get_int_reinterpret(tc_in);
	cout << "Ap_fixed variables initialized for software sim, mode=" << mode_in_u32 << " t=" << t_in << " ts=" << ts_in << " tc=" << tc_in << endl;
	XCordic_Initialize(&Cordic, 0);
	XCordic_Set_select_r(&Cordic, mode_in_u32);
	XCordic_Set_CS_I_T(&Cordic, t_in_u32);
	XCordic_Set_IA_I_S(&Cordic, ts_in_u32);
	XCordic_Set_IA_I_C(&Cordic, tc_in_u32);
    XCordic_Start(&Cordic);
	while (!XCordic_IsReady(&Cordic));
	done_out = XCordic_Get_done(&Cordic);
	CS_O_SIN_u32 = XCordic_Get_CS_O_SIN(&Cordic);
	CS_O_COS_u32 = XCordic_Get_CS_O_COS(&Cordic);
	IA_O_IAT_u32 = XCordic_Get_IA_O_IAT(&Cordic);
	cout << "Done signal from hardware = " << done_out << endl;
	CS_O_COS = get_fixed_reinterpret(CS_O_COS_u32);
	CS_O_SIN = get_fixed_reinterpret(CS_O_SIN_u32);
	printf("result sin = %f, cos = %f\n", (float)CS_O_SIN, (float)CS_O_COS);

//	unsigned int debugSelect  = XCordic_Get_select_r(&Cordic);
//	printf("result debugSelect = %d\n", debugSelect);
//	printf("result debugSelectSend = %d\n", mode_in_u32);


	mode_in_u32 = 1;
	t_in_u32 = get_int_reinterpret(t_in);
	ts_in_u32 = get_int_reinterpret(ts_in);
	tc_in_u32 = get_int_reinterpret(tc_in);
	cout << "Ap_fixed variables initialized for software sim, mode=" << mode_in_u32 << " t=" << t_in << " ts=" << ts_in << " tc=" << tc_in << endl;
	XCordic_Initialize(&Cordic, 0);
	XCordic_Set_select_r(&Cordic, mode_in_u32);
	XCordic_Set_CS_I_T(&Cordic, t_in_u32);
	XCordic_Set_IA_I_S(&Cordic, ts_in_u32);
	XCordic_Set_IA_I_C(&Cordic, tc_in_u32);
	XCordic_Start(&Cordic);
	while (!XCordic_IsReady(&Cordic));
	done_out = XCordic_Get_done(&Cordic);
	CS_O_SIN_u32 = XCordic_Get_CS_O_SIN(&Cordic);
	CS_O_COS_u32 = XCordic_Get_CS_O_COS(&Cordic);
	IA_O_IAT_u32 = XCordic_Get_IA_O_IAT(&Cordic);
	cout << "Done signal from hardware = " << done_out << endl;
	IA_O_IAT = get_fixed_reinterpret(IA_O_IAT_u32);
	printf("result theta = %f\n", (float)IA_O_IAT / PI * 180.0);


    cout << "--- End of the Program ---" << endl;


	return 0;
}

