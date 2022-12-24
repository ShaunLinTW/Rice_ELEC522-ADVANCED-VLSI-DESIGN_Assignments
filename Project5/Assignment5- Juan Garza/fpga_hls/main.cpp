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


#include <iostream>

#include <stdio.h>
//#include "platform.h"
#include "xil_printf.h"
#include <unistd.h>
//#include "treeadd.h"
#include "xtime_l.h"
#include "xparameters.h"
// The Xilinx time function file for measuring ARM core cycles
#include "xtime_l.h"
// Xilinx function for interrupt controller - may not be used in polling example.
#include "xscugic.h"
#include "ap_fixed.h"
#include "arm_core_design_block.h"
// .h file based on your original .hls design input
//#include "t_fixed.h"


// .h file from export to IP Creator from VitisHLS. This file is in the repository added to Vitis
// It will be copied from the drivers folder to the local in my example at
// C:\ELEC522\cavallar\Tree_Fixed_HLS_Vitis\Vitis\design_1_wrapper\ps7_cortex9_0\standalone_ps7_c\include
//#include "xt_fixed.h"
//#include "xcordic.h"
//nclude "xarm_core_design_block.h""



// Add the include path C:\Xilinx\Vitis_HLS\2021.1\include to Vitis project properties
// Add this, right click on the project name to access C/C++ Build Settings then C/C++ General
// Finally add path to Paths and Symbols, include directory
// For the c++ file for the fixed point data type


// IMPORTANT HLS t_fixed HW instance - Needed pointer - see the xt_fixed.h file
//XT_fixed T_fixed;
//XCordic Cordic;
arm_core_design_block Arm_core_design_block;
// The Board Support Package that Vitis builds when you start a project should have these files
// Memory map file from
// C:\ELEC522\cavallar\Tree_Fixed_HLS_Vitis\Vitis\design_1_wrapper\ps7_cortexa9_0\standalone_ps7_cortexa9_0\bsp\ps7_cortexa9_0\include\



// Used by C++ for the print command cout
using namespace std;
// Define our fixed point type used here to match the PL accelerator
typedef ap_fixed<16, 3, AP_RND, AP_SAT> FIXED_TYPE;

// The AXI interface sends only "raw bits" so we need to convert standard data types we use to
// match the ap_fixed data type in the PL accelerator.
// Using C++ functions per - RJ Cunningham
int get_int_reinterpret(FIXED_TYPE x) {
	return *(reinterpret_cast<short*>(&x));
}

FIXED_TYPE get_fixed_reinterpret(int x) {
	return *(reinterpret_cast<FIXED_TYPE*>(&x));
}


// actual MAIN control program running on ARM processor PS


void delay_ms(unsigned int mseconds)
{
	XTime tEnd, tCur;

	XTime_GetTime(&tCur);
	tEnd = tCur + (((XTime)mseconds) * (COUNTS_PER_SECOND / 1000));
	do
	{
		XTime_GetTime(&tCur);
	} while (tCur < tEnd);
}



int main()
{
	cout << "--- Start of the Program ---" << endl;

	// inputs
	FIXED_TYPE a11 = 0.8799;
	FIXED_TYPE a21 = 0.3401;
	FIXED_TYPE a31 = 0.3784;
	FIXED_TYPE a41 = 0.6900;

	FIXED_TYPE a12 = 0.3194;
	FIXED_TYPE a22 = 0.8434;
	FIXED_TYPE a32 = 0.2577;
	FIXED_TYPE a42 = 0.5054;

	FIXED_TYPE a13 = 0.9805;
	FIXED_TYPE a23 = 0.0687;
	FIXED_TYPE a33 = 0.2073;
	FIXED_TYPE a43 = 0.5914;

	FIXED_TYPE a14 = 0.0850;
	FIXED_TYPE a24 = 0.4099;
	FIXED_TYPE a34 = 0.6262;
	FIXED_TYPE a44 = 0.5547;
	bool rst;
	bool start;
	rst = false;
	start = false;
	//cout << "\n a11:" << a11 << ",  a12: " << a12 << ",  a13: " << a13 << ",  a14:" << a14 << endl;
	//cout << "\n ua11:" << ua11 << ",  ua12: " << ua21 << ",  ua13: " << ua31 << ",  a14:" << ua41 << endl;

	signed int ua11 = get_int_reinterpret(a11);
	signed int ua21 = get_int_reinterpret(a21);
	signed int ua31 = get_int_reinterpret(a31);
	signed int ua41 = get_int_reinterpret(a41);

	signed int ua12 = get_int_reinterpret(a12);
	signed int ua22 = get_int_reinterpret(a22);
	signed int ua32 = get_int_reinterpret(a32);
	signed int ua42 = get_int_reinterpret(a42);


	signed int ua13 = get_int_reinterpret(a13);
	signed int ua23 = get_int_reinterpret(a23);
	signed int ua33 = get_int_reinterpret(a33);
	signed int ua43 = get_int_reinterpret(a43);

	signed int ua14 = get_int_reinterpret(a14);
	signed int ua24 = get_int_reinterpret(a24);
	signed int ua34 = get_int_reinterpret(a34);
	signed int ua44 = get_int_reinterpret(a44);


	//
	signed int uor11, uor12, uor13, uor14;
	signed int        uor22, uor32, uor24;
	signed int  	         uor33, uor34;
	signed int 				        uor44;

	signed int uoq11, uoq21, uoq31, uoq41;
	signed int uoq12, uoq22, uoq32, uoq42;
	signed int uoq13, uoq23, uoq33, uoq43;
	signed int uoq14, uoq24, uoq34, uoq44;


	FIXED_TYPE or11, or21, or31, or41;
	FIXED_TYPE or12, or22, or32, or42;
	FIXED_TYPE or13, or23, or33, or43;
	FIXED_TYPE or14, or24, or34, or44;

	FIXED_TYPE oq11, oq21, oq31, oq41;
	FIXED_TYPE oq12, oq22, oq32, oq42;
	FIXED_TYPE oq13, oq23, oq33, oq43;
	FIXED_TYPE oq14, oq24, oq34, oq44;


	//	XCordic_Initialize(&Cordic, 0)
	arm_core_design_block_Initialize(&Arm_core_design_block, 0);


	arm_core_design_block_a11_var_write(&Arm_core_design_block, ua11);
	arm_core_design_block_a21_var_write(&Arm_core_design_block, ua21);
	arm_core_design_block_a31_var_write(&Arm_core_design_block, ua31);
	arm_core_design_block_a41_var_write(&Arm_core_design_block, ua41);

	arm_core_design_block_a12_var_write(&Arm_core_design_block, ua12);
	arm_core_design_block_a22_var_write(&Arm_core_design_block, ua22);
	arm_core_design_block_a32_var_write(&Arm_core_design_block, ua32);
	arm_core_design_block_a42_var_write(&Arm_core_design_block, ua42);

	arm_core_design_block_a13_var_write(&Arm_core_design_block, ua13);
	arm_core_design_block_a23_var_write(&Arm_core_design_block, ua23);
	arm_core_design_block_a33_var_write(&Arm_core_design_block, ua33);
	arm_core_design_block_a43_var_write(&Arm_core_design_block, ua43);


	arm_core_design_block_a14_var_write(&Arm_core_design_block, ua14);
	arm_core_design_block_a24_var_write(&Arm_core_design_block, ua24);
	arm_core_design_block_a34_var_write(&Arm_core_design_block, ua34);
	arm_core_design_block_a44_var_write(&Arm_core_design_block, ua44);

	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);

	delay_ms(100);
	arm_core_design_block_rst_var_write(&Arm_core_design_block, false);
	arm_core_design_block_start_var_write(&Arm_core_design_block, false);

	delay_ms(500);
	arm_core_design_block_start_var_write(&Arm_core_design_block, true);

	delay_ms(5000);
	//sleep
	//	R matrix
	uor11 = arm_core_design_block_rout_11_read(&Arm_core_design_block);

	uor12 = arm_core_design_block_rout_21_read(&Arm_core_design_block);
	uor22 = arm_core_design_block_rout_22_read(&Arm_core_design_block);

	uor13 = arm_core_design_block_rout_31_read(&Arm_core_design_block);
	uor32 = arm_core_design_block_rout_32_read(&Arm_core_design_block);
	uor33 = arm_core_design_block_rout_33_read(&Arm_core_design_block);

	uor14 = arm_core_design_block_rout_41_read(&Arm_core_design_block);
	uor24 = arm_core_design_block_rout_42_read(&Arm_core_design_block);
	uor34 = arm_core_design_block_rout_43_read(&Arm_core_design_block);
	uor44 = arm_core_design_block_rout_44_read(&Arm_core_design_block);

	//	Q matrix
	uoq11 = arm_core_design_block_qout_11_read(&Arm_core_design_block);
	uoq12 = arm_core_design_block_qout_12_read(&Arm_core_design_block);
	uoq13 = arm_core_design_block_qout_13_read(&Arm_core_design_block);
	uoq14 = arm_core_design_block_qout_14_read(&Arm_core_design_block);

	uoq21 = arm_core_design_block_qout_21_read(&Arm_core_design_block);
	uoq22 = arm_core_design_block_qout_22_read(&Arm_core_design_block);
	uoq23 = arm_core_design_block_qout_23_read(&Arm_core_design_block);
	uoq24 = arm_core_design_block_qout_24_read(&Arm_core_design_block);

	uoq31 = arm_core_design_block_qout_31_read(&Arm_core_design_block);
	uoq32 = arm_core_design_block_qout_32_read(&Arm_core_design_block);
	uoq33 = arm_core_design_block_qout_33_read(&Arm_core_design_block);
	uoq34 = arm_core_design_block_qout_34_read(&Arm_core_design_block);

	uoq41 = arm_core_design_block_qout_41_read(&Arm_core_design_block);
	uoq42 = arm_core_design_block_qout_42_read(&Arm_core_design_block);
	uoq43 = arm_core_design_block_qout_43_read(&Arm_core_design_block);
	uoq44 = arm_core_design_block_qout_44_read(&Arm_core_design_block);





	//	  R out
	or11 = get_fixed_reinterpret(uor11);

	or12 = get_fixed_reinterpret(uor12);
	or22 = get_fixed_reinterpret(uor22);

	or13 = get_fixed_reinterpret(uor13);
	or23 = get_fixed_reinterpret(uor32);
	or33 = get_fixed_reinterpret(uor33);

	or14 = get_fixed_reinterpret(uor14);
	or24 = get_fixed_reinterpret(uor24);
	or34 = get_fixed_reinterpret(uor34);
	or44 = get_fixed_reinterpret(uor44);

	//Q output
	oq11 = get_fixed_reinterpret(uoq11);
	oq12 = get_fixed_reinterpret(uoq12);
	oq13 = get_fixed_reinterpret(uoq13);
	oq14 = get_fixed_reinterpret(uoq14);

	oq21 = get_fixed_reinterpret(uoq21);
	oq22 = get_fixed_reinterpret(uoq22);
	oq23 = get_fixed_reinterpret(uoq23);
	oq24 = get_fixed_reinterpret(uoq24);

	oq31 = get_fixed_reinterpret(uoq31);
	oq32 = get_fixed_reinterpret(uoq32);
	oq33 = get_fixed_reinterpret(uoq33);
	oq34 = get_fixed_reinterpret(uoq34);

	oq41 = get_fixed_reinterpret(uoq41);
	oq42 = get_fixed_reinterpret(uoq42);
	oq43 = get_fixed_reinterpret(uoq43);
	oq44 = get_fixed_reinterpret(uoq44);


	cout << "--------------------Praying for it working MODE--------------------" << endl;



	or21 = 0.00000;
	or31 = 0.00000; or32 = 0.00000;
	or41 = 0.00000; or42 = 0.00000;  or43 = 0.00000;


	cout << "\n--------------------A1--------------------" << endl;
	cout << "\n {" << a11 << ", " << a12 << ", " << a13 << ", " << a14 << "}, " << endl;
	cout << "\n {" << a21 << ", " << a22 << ", " << a23 << ", " << a24 << "}, " << endl;
	cout << "\n {" << a31 << ", " << a32 << ", " << a33 << ", " << a34 << "}, " << endl;
	cout << "\n {" << a41 << ", " << a42 << ", " << a43 << ", " << a44 << "}} " << endl;


	cout << "--------------------R1--------------------" << endl;

	cout << "\n {" << or11 << ", " << or12 << ", " << or13 << ", " << or14 << "}, " << endl;
	cout << "\n {0.00000," << or22 << ", " << or23 << ", " << or24 << "}, " << endl;
	cout << "\n {0.00000, 0.00000, " << or33 << ", " << or34 << "}, " << endl;
	cout << "\n {0.00000, 0.00000, 0.00000, " << or44 << "}} " << endl;

	cout << "--------------------Q1--------------------" << endl;

	cout << "\n {" << oq11 << ", " << oq21 << ", " << oq31 << ", " << oq41 << "}, " << endl;
	cout << "\n {" << oq12 << ", " << oq22 << ", " << oq32 << ", " << oq42 << "}, " << endl;
	cout << "\n {" << oq13 << ", " << oq23 << ", " << oq33 << ", " << oq43 << "}, " << endl;
	cout << "\n {" << oq14 << ", " << oq24 << ", " << oq34 << ", " << oq44 << "}} " << endl;


	cout << "\n --------------------*Next Matrix*--------------------" << endl;



	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);

	a11 = 0.1845;
	a21 = 0.6496;
	a31 = 0.1345;
	a41 = 0.9629;

	a12 = 0.7026;
	a22 = 0.9629;
	a32 = 0.5616;
	a42 = 0.2118;

	a13 = 0.7124;
	a23 = 0.7813;
	a33 = 0.1008;
	a43 = 0.8349;

	a14 = 0.6811;
	a24 = 0.9637;
	a34 = 0.9517;
	a44 = 0.4713;

	ua11 = get_int_reinterpret(a11);
	ua21 = get_int_reinterpret(a21);
	ua31 = get_int_reinterpret(a31);
	ua41 = get_int_reinterpret(a41);

	ua12 = get_int_reinterpret(a12);
	ua22 = get_int_reinterpret(a22);
	ua32 = get_int_reinterpret(a32);
	ua42 = get_int_reinterpret(a42);

	ua13 = get_int_reinterpret(a13);
	ua23 = get_int_reinterpret(a23);
	ua33 = get_int_reinterpret(a33);
	ua43 = get_int_reinterpret(a43);

	ua14 = get_int_reinterpret(a14);
	ua24 = get_int_reinterpret(a24);
	ua34 = get_int_reinterpret(a34);
	ua44 = get_int_reinterpret(a44);


	delay_ms(200);

	arm_core_design_block_a11_var_write(&Arm_core_design_block, ua11);
	arm_core_design_block_a21_var_write(&Arm_core_design_block, ua21);
	arm_core_design_block_a31_var_write(&Arm_core_design_block, ua31);
	arm_core_design_block_a41_var_write(&Arm_core_design_block, ua41);

	arm_core_design_block_a12_var_write(&Arm_core_design_block, ua12);
	arm_core_design_block_a22_var_write(&Arm_core_design_block, ua22);
	arm_core_design_block_a32_var_write(&Arm_core_design_block, ua32);
	arm_core_design_block_a42_var_write(&Arm_core_design_block, ua42);

	arm_core_design_block_a13_var_write(&Arm_core_design_block, ua13);
	arm_core_design_block_a23_var_write(&Arm_core_design_block, ua23);
	arm_core_design_block_a33_var_write(&Arm_core_design_block, ua33);
	arm_core_design_block_a43_var_write(&Arm_core_design_block, ua43);


	arm_core_design_block_a14_var_write(&Arm_core_design_block, ua14);
	arm_core_design_block_a24_var_write(&Arm_core_design_block, ua24);
	arm_core_design_block_a34_var_write(&Arm_core_design_block, ua34);
	arm_core_design_block_a44_var_write(&Arm_core_design_block, ua44);

	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);

	delay_ms(100);
	arm_core_design_block_rst_var_write(&Arm_core_design_block, false);
	arm_core_design_block_start_var_write(&Arm_core_design_block, false);

	delay_ms(500);
	arm_core_design_block_start_var_write(&Arm_core_design_block, true);

	delay_ms(5000);
	//sleep
	//	R matrix
	uor11 = arm_core_design_block_rout_11_read(&Arm_core_design_block);

	uor12 = arm_core_design_block_rout_21_read(&Arm_core_design_block);
	uor22 = arm_core_design_block_rout_22_read(&Arm_core_design_block);

	uor13 = arm_core_design_block_rout_31_read(&Arm_core_design_block);
	uor32 = arm_core_design_block_rout_32_read(&Arm_core_design_block);
	uor33 = arm_core_design_block_rout_33_read(&Arm_core_design_block);

	uor14 = arm_core_design_block_rout_41_read(&Arm_core_design_block);
	uor24 = arm_core_design_block_rout_42_read(&Arm_core_design_block);
	uor34 = arm_core_design_block_rout_43_read(&Arm_core_design_block);
	uor44 = arm_core_design_block_rout_44_read(&Arm_core_design_block);

	//Q matrix
	uoq11 = arm_core_design_block_qout_11_read(&Arm_core_design_block);
	uoq12 = arm_core_design_block_qout_12_read(&Arm_core_design_block);
	uoq13 = arm_core_design_block_qout_13_read(&Arm_core_design_block);
	uoq14 = arm_core_design_block_qout_14_read(&Arm_core_design_block);

	uoq21 = arm_core_design_block_qout_21_read(&Arm_core_design_block);
	uoq22 = arm_core_design_block_qout_22_read(&Arm_core_design_block);
	uoq23 = arm_core_design_block_qout_23_read(&Arm_core_design_block);
	uoq24 = arm_core_design_block_qout_24_read(&Arm_core_design_block);

	uoq31 = arm_core_design_block_qout_31_read(&Arm_core_design_block);
	uoq32 = arm_core_design_block_qout_32_read(&Arm_core_design_block);
	uoq33 = arm_core_design_block_qout_33_read(&Arm_core_design_block);
	uoq34 = arm_core_design_block_qout_34_read(&Arm_core_design_block);

	uoq41 = arm_core_design_block_qout_41_read(&Arm_core_design_block);
	uoq42 = arm_core_design_block_qout_42_read(&Arm_core_design_block);
	uoq43 = arm_core_design_block_qout_43_read(&Arm_core_design_block);
	uoq44 = arm_core_design_block_qout_44_read(&Arm_core_design_block);





	//R out
	or11 = get_fixed_reinterpret(uor11);

	or12 = get_fixed_reinterpret(uor12);
	or22 = get_fixed_reinterpret(uor22);

	or13 = get_fixed_reinterpret(uor13);
	or23 = get_fixed_reinterpret(uor32);
	or33 = get_fixed_reinterpret(uor33);

	or14 = get_fixed_reinterpret(uor14);
	or24 = get_fixed_reinterpret(uor24);
	or34 = get_fixed_reinterpret(uor34);
	or44 = get_fixed_reinterpret(uor44);

	//Q output
	oq11 = get_fixed_reinterpret(uoq11);
	oq12 = get_fixed_reinterpret(uoq12);
	oq13 = get_fixed_reinterpret(uoq13);
	oq14 = get_fixed_reinterpret(uoq14);

	oq21 = get_fixed_reinterpret(uoq21);
	oq22 = get_fixed_reinterpret(uoq22);
	oq23 = get_fixed_reinterpret(uoq23);
	oq24 = get_fixed_reinterpret(uoq24);

	oq31 = get_fixed_reinterpret(uoq31);
	oq32 = get_fixed_reinterpret(uoq32);
	oq33 = get_fixed_reinterpret(uoq33);
	oq34 = get_fixed_reinterpret(uoq34);

	oq41 = get_fixed_reinterpret(uoq41);
	oq42 = get_fixed_reinterpret(uoq42);
	oq43 = get_fixed_reinterpret(uoq43);
	oq44 = get_fixed_reinterpret(uoq44);



	cout << "\n--------------------A2--------------------" << endl;

	cout << "\n {" << a11 << ", " << a12 << ", " << a13 << ", " << a14 << "}, " << endl;
	cout << "\n {" << a21 << ", " << a22 << ", " << a23 << ", " << a24 << "}, " << endl;
	cout << "\n {" << a31 << ", " << a32 << ", " << a33 << ", " << a34 << "}, " << endl;
	cout << "\n {" << a41 << ", " << a42 << ", " << a43 << ", " << a44 << "}} " << endl;



	cout << "\n--------------------R2--------------------" << endl;

	cout << "\n {" << or11 << ", " << or12 << ", " << or13 << ", " << or14 << "}, " << endl;
	cout << "\n {0.00000," << or22 << ", " << or23 << ", " << or24 << "}, " << endl;
	cout << "\n {0.00000, 0.00000, " << or33 << ", " << or34 << "}, " << endl;
	cout << "\n {0.00000, 0.00000, 0.00000, " << or44 << "}} " << endl;

	cout << "--------------------Q2--------------------" << endl;

	cout << "\n {" << oq11 << ", " << oq21 << ", " << oq31 << ", " << oq41 << "}, " << endl;
	cout << "\n {" << oq12 << ", " << oq22 << ", " << oq32 << ", " << oq42 << "}, " << endl;
	cout << "\n {" << oq13 << ", " << oq23 << ", " << oq33 << ", " << oq43 << "}, " << endl;
	cout << "\n {" << oq14 << ", " << oq24 << ", " << oq34 << ", " << oq44 << "}} " << endl;






















	//	cout << "\nor11 " << or11 << or21 << or31 << or41 << endl;
	//reinterpret
	// values for simulation and testing using C++ format with ap_fixed
	//inputs	COS_SIN_TYPE x;COS_SIN_TYPE y;	THETA_TYPE theta;	bool state;
	//outputs	COS_SIN_TYPE c;	COS_SIN_TYPE s;	COS_SIN_TYPE t;
	//	FIXED_TYPE a_in = 1.2;
	// values for sending over AXI bus to programmable logic (PL)
	//signed int state_u32, theta_u32, x_u32, y_u32, s_out_u32, c_out_u32, t_out_u32;
	//void cordic(bool state, THETA_TYPE theta, COS_SIN_TYPE x, COS_SIN_TYPE y, COS_SIN_TYPE &s, COS_SIN_TYPE &c, THETA_TYPE_in &t);
	//sin/cos mode


	/*x = 1; 	y = 0; 	state = true; 	int angle = 0; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {    s_out_u32 = XCordic_Get_s(&Cordic);    c_out_u32 = XCordic_Get_c(&Cordic);    t_out_u32 = XCordic_Get_t(&Cordic);}
	while (!XCordic_IsReady(&Cordic));  while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32); 	s = get_fixed_reinterpret(s_out_u32);  c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	x = 1; 	y = 0; 	state = true;  angle = 15; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);      }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32); */


	return 0;
}








