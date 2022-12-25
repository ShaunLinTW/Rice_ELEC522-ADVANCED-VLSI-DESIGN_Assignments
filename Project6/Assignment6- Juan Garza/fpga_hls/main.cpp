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
#include <math.h>

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

void delay_us(unsigned int useconds)
{
	XTime tEnd, tCur;

	XTime_GetTime(&tCur);
	tEnd = tCur + (((XTime)useconds) * (COUNTS_PER_SECOND / 1000000));
	do
	{
		XTime_GetTime(&tCur);
	} while (tCur < tEnd);
}





void hardware_des(FIXED_TYPE mat_in[4][4], FIXED_TYPE b_in[4]) {

	FIXED_TYPE a11 = mat_in[0][0];
	FIXED_TYPE a21 = mat_in[1][0];
	FIXED_TYPE a31 = mat_in[2][0];
	FIXED_TYPE a41 = mat_in[3][0];

	FIXED_TYPE a12 = mat_in[0][1];
	FIXED_TYPE a22 = mat_in[1][1];
	FIXED_TYPE a32 = mat_in[2][1];
	FIXED_TYPE a42 = mat_in[3][1];

	FIXED_TYPE a13 = mat_in[0][2];
	FIXED_TYPE a23 = mat_in[1][2];
	FIXED_TYPE a33 = mat_in[2][2];
	FIXED_TYPE a43 = mat_in[3][2];

	FIXED_TYPE a14 = mat_in[0][3];
	FIXED_TYPE a24 = mat_in[1][3];
	FIXED_TYPE a34 = mat_in[2][3];
	FIXED_TYPE a44 = mat_in[3][3];

	FIXED_TYPE b1 = b_in[0];
	FIXED_TYPE b2 = b_in[1];
	FIXED_TYPE b3 = b_in[2];
	FIXED_TYPE b4 = b_in[3];



	bool rst;
	bool start;
	rst = false;
	start = false;
	//cout << "\n a11:" << a11 << ",  a12: " << a12 << ",  a13: " << a13 << ",  a14:" << a14 << endl;
	//cout << "\n ua11:" << ua11 << ",  ua12: " << ua21 << ",  ua13: " << ua31 << ",  a14:" << ua41 << endl;


//	FIXED_TYPE b1 = b_vect[0];

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


	signed int ub1 = get_int_reinterpret(b1);
	signed int ub2 = get_int_reinterpret(b2);
	signed int ub3 = get_int_reinterpret(b3);
	signed int ub4 = get_int_reinterpret(b4);


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

	signed int uqout1, uqout2, uqout3, uqout4;


	arm_core_design_block_rst_var_write(&Arm_core_design_block, false);

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

	arm_core_design_block_b_1_write(&Arm_core_design_block, ub1);
	arm_core_design_block_b_2_write(&Arm_core_design_block, ub2);
	arm_core_design_block_b_3_write(&Arm_core_design_block, ub3);
	arm_core_design_block_b_4_write(&Arm_core_design_block, ub4);

	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);

	//delay_us(1);
	arm_core_design_block_start_var_write(&Arm_core_design_block, false);
	arm_core_design_block_rst_var_write(&Arm_core_design_block, false);

	//delay_us(1);

	//	delay_ms(100);
	arm_core_design_block_start_var_write(&Arm_core_design_block, true);

	while (true) {
		if (arm_core_design_block_done_var_read(&Arm_core_design_block)) {
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


			uqout1 = arm_core_design_block_qout_1_read(&Arm_core_design_block);
			uqout2 = arm_core_design_block_qout_2_read(&Arm_core_design_block);
			uqout3 = arm_core_design_block_qout_3_read(&Arm_core_design_block);
			uqout4 = arm_core_design_block_qout_4_read(&Arm_core_design_block);
			break;

		}
	}




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


	cout << "\n--------------------Ai--------------------" << endl;
	cout << "\n {" << a11 << ", " << a12 << ", " << a13 << ", " << a14 << "}, " << endl;
	cout << "\n {" << a21 << ", " << a22 << ", " << a23 << ", " << a24 << "}, " << endl;
	cout << "\n {" << a31 << ", " << a32 << ", " << a33 << ", " << a34 << "}, " << endl;
	cout << "\n {" << a41 << ", " << a42 << ", " << a43 << ", " << a44 << "}} " << endl;


	cout << "--------------------Ri--------------------" << endl;

	cout << "\n {" << or11 << ", " << or12 << ", " << or13 << ", " << or14 << "}, " << endl;
	cout << "\n {0.00000," << or22 << ", " << or23 << ", " << or24 << "}, " << endl;
	cout << "\n {0.00000, 0.00000, " << or33 << ", " << or34 << "}, " << endl;
	cout << "\n {0.00000, 0.00000, 0.00000, " << or44 << "}} " << endl;

	cout << "--------------------Qi--------------------" << endl;

	cout << "\n {" << oq11 << ", " << oq21 << ", " << oq31 << ", " << oq41 << "}, " << endl;
	cout << "\n {" << oq12 << ", " << oq22 << ", " << oq32 << ", " << oq42 << "}, " << endl;
	cout << "\n {" << oq13 << ", " << oq23 << ", " << oq33 << ", " << oq43 << "}, " << endl;
	cout << "\n {" << oq14 << ", " << oq24 << ", " << oq34 << ", " << oq44 << "}} " << endl;


	cout << "\n --------------------*Next Matrix*--------------------" << endl;

	FIXED_TYPE oqout1, oqout2, oqout3, oqout4;

	oqout1 = get_fixed_reinterpret(uqout1);
	oqout2 = get_fixed_reinterpret(uqout2);
	oqout3 = get_fixed_reinterpret(uqout3);
	oqout4 = get_fixed_reinterpret(uqout4);

	cout << "\n b {" << b_in[0] << ", " << b_in[1] << ", " << b_in[2] << ", " << b_in[3] << "} " << endl;

	cout << "\n qTb {" << oqout1 << ", " << oqout2 << ", " << oqout3 << ", " << oqout4 << "} " << endl;

	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);
	//back subsitution
	FIXED_TYPE x4_out = oqout4 / or44;
	FIXED_TYPE x3_out = (oqout3 - x4_out * or34) / or33;
	FIXED_TYPE x2_out = (oqout2 - x3_out * or23 - x4_out * or24) / or22;
	FIXED_TYPE x1_out = (oqout1 - x2_out * or12 - x3_out * or13 - x4_out * or14) / or11;
	cout << "\n X_v =  {" << x1_out << ", " << x2_out << ", " << x3_out << ", " << x4_out << "} " << endl;
}

void hardware_des_time(FIXED_TYPE mat_in[4][4], FIXED_TYPE b_in[4]) {

	FIXED_TYPE a11 = mat_in[0][0];
	FIXED_TYPE a21 = mat_in[1][0];
	FIXED_TYPE a31 = mat_in[2][0];
	FIXED_TYPE a41 = mat_in[3][0];

	FIXED_TYPE a12 = mat_in[0][1];
	FIXED_TYPE a22 = mat_in[1][1];
	FIXED_TYPE a32 = mat_in[2][1];
	FIXED_TYPE a42 = mat_in[3][1];

	FIXED_TYPE a13 = mat_in[0][2];
	FIXED_TYPE a23 = mat_in[1][2];
	FIXED_TYPE a33 = mat_in[2][2];
	FIXED_TYPE a43 = mat_in[3][2];

	FIXED_TYPE a14 = mat_in[0][3];
	FIXED_TYPE a24 = mat_in[1][3];
	FIXED_TYPE a34 = mat_in[2][3];
	FIXED_TYPE a44 = mat_in[3][3];

	FIXED_TYPE b1 = b_in[0];
	FIXED_TYPE b2 = b_in[1];
	FIXED_TYPE b3 = b_in[2];
	FIXED_TYPE b4 = b_in[3];



	bool rst;
	bool start;
	rst = false;
	start = false;

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


	signed int ub1 = get_int_reinterpret(b1);
	signed int ub2 = get_int_reinterpret(b2);
	signed int ub3 = get_int_reinterpret(b3);
	signed int ub4 = get_int_reinterpret(b4);


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

	signed int uqout1, uqout2, uqout3, uqout4;


	arm_core_design_block_rst_var_write(&Arm_core_design_block, false);

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

	arm_core_design_block_b_1_write(&Arm_core_design_block, ub1);
	arm_core_design_block_b_2_write(&Arm_core_design_block, ub2);
	arm_core_design_block_b_3_write(&Arm_core_design_block, ub3);
	arm_core_design_block_b_4_write(&Arm_core_design_block, ub4);

	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);

	//delay_us(1);
	arm_core_design_block_start_var_write(&Arm_core_design_block, false);
	arm_core_design_block_rst_var_write(&Arm_core_design_block, false);

	//delay_us(1);

	//	delay_ms(100);
	arm_core_design_block_start_var_write(&Arm_core_design_block, true);

	while (true) {
		if (arm_core_design_block_done_var_read(&Arm_core_design_block)) {
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


			uqout1 = arm_core_design_block_qout_1_read(&Arm_core_design_block);
			uqout2 = arm_core_design_block_qout_2_read(&Arm_core_design_block);
			uqout3 = arm_core_design_block_qout_3_read(&Arm_core_design_block);
			uqout4 = arm_core_design_block_qout_4_read(&Arm_core_design_block);
			break;

		}
	}

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



	FIXED_TYPE oqout1, oqout2, oqout3, oqout4;

	oqout1 = get_fixed_reinterpret(uqout1);
	oqout2 = get_fixed_reinterpret(uqout2);
	oqout3 = get_fixed_reinterpret(uqout3);
	oqout4 = get_fixed_reinterpret(uqout4);
	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);
	//back subsitution
	FIXED_TYPE x4_out = oqout4 / or44;
	FIXED_TYPE x3_out = (oqout3 - x4_out * or34) / or33;
	FIXED_TYPE x2_out = (oqout2 - x3_out * or23 - x4_out * or24) / or22;
	FIXED_TYPE x1_out = (oqout1 - x2_out * or12 - x3_out * or13 - x4_out * or14) / or11;
	cout << "\n X_v =  {" << x1_out << ", " << x2_out << ", " << x3_out << ", " << x4_out << "} " << endl;

	//x4sw = qtb(4) / r(4,4) .';
	//x3sw = (qtb(3) - x4sw* r(3,4))/r(3,3) .';
	//x2sw = (qtb(2) - x3sw*r(2,3) - x4sw*r(2,4))/r(2,2) .';
	//x1sw = (qtb(1) - x2sw*r(1,2) - x3sw*r(1,3) - x4sw*r(1,4))/r(1,1) .';

}

void matrix_mult(double A[4][4], double B[4][4], double res[4][4]) {

	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			res[i][j] = 0;
			for (k = 0; k < 4; k++)
			{
				res[i][j] += A[i][k] * B[k][j];
			}
		}

	}
}

void matrix_vect(double A[4][4], double B[4], double res[4]) {

	int i, j;
	for (i = 0; i < 4; i++) {
		res[i] = 0;
		for (j = 0; j < 4; j++) {
			res[i] += A[i][j] * B[j];

		}

	}
}

void AasissignB(double A[4][4], double B[4][4]) {

	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			B[i][j] = A[i][j];
		}
	}
}

void transAtoB(double A[4][4], double B[4][4]) {

	int i, j;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			B[i][j] = A[j][i];
		}
	}
}



void sw_des(double R_mat[4][4], double b_vect[4]) {
	cout << "--------------------Next Matrix--------------------" << endl;

	double Gn[4][4];
	double Q[4][4];

	int n = 4;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				Gn[i][j] = 1;
				Q[i][j] = 1;
			}
			else {
				Gn[i][j] = 0;
				Q[i][j] = 0;
			}
		}
	}


	int iteration = 1;
	double a = R_mat[0][n - 2];
	double b = R_mat[0][n - 1];
	double X_var;
	double Y_var;
	double intermed[4][4];


	for (int i = 0; i < n; i++) {
		for (int j = (n - 1); j > i; j--) {

			a = R_mat[j - 1][i];
			b = R_mat[j][i];
			X_var = a / (sqrt(a * a + b * b));
			Y_var = -b / (sqrt(a * a + b * b));

			Gn[j][j] = X_var;
			Gn[j][j - 1] = Y_var;
			Gn[j - 1][j] = -Y_var;
			Gn[j - 1][j - 1] = X_var;

			matrix_mult(Gn, R_mat, intermed);
			AasissignB(intermed, R_mat);

			matrix_mult(Gn, Q, intermed);
			AasissignB(intermed, Q);


			for (int ident = 0; ident < n; ident++) {
				for (int ident2 = 0; ident2 < n; ident2++) {
					if (ident == ident2)
						Gn[ident][ident2] = 1;
					else
						Gn[ident][ident2] = 0;
				}
			}
			iteration += 1;
		}
	}
	transAtoB(Q, intermed);

	cout << "R:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%.4f ", R_mat[i][j]);
		}
		cout << endl;
	}

	cout << "Q:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%.4f ", intermed[i][j]);
		}
		cout << endl;
	}
	double qtb[4];
	matrix_vect(Q, b_vect, qtb);
	double x4_out = qtb[3] / R_mat[3][3];
	double x3_out = (qtb[2] - x4_out * R_mat[2][3]) / R_mat[2][2];
	double x2_out = (qtb[1] - x3_out * R_mat[1][2] - x4_out * R_mat[1][3]) / R_mat[1][1];
	double x1_out = (qtb[0] - x2_out * R_mat[0][1] - x3_out * R_mat[0][2] - x4_out * R_mat[0][3]) / R_mat[0][0];

	double x_sw_out[4] = { x1_out, x2_out,x3_out , x4_out };

	cout << "Qtb:" << endl;
	for (int i = 0; i < n; i++)
	{

		printf("%.4f ", qtb[i]);

		cout << endl;
	}

	cout << "X_in:" << endl;
	for (int i = 0; i < n; i++)
	{

		printf("%.4f ", x_sw_out[i]);

		cout << endl;
	}


	matrix_mult(intermed, R_mat, Q);
	cout << "A?:" << endl;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%.4f ", Q[i][j]);
		}
		cout << endl;
	}

}




void sw_des_time(double R_mat[4][4], double b_vect[4]) {
	double Gn[4][4];
	double Q[4][4];
	int n = 4;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == j) {
				Gn[i][j] = 1;
				Q[i][j] = 1;
			}
			else {
				Gn[i][j] = 0;
				Q[i][j] = 0;
			}
		}
	}
	int iteration = 1;
	double a = R_mat[0][n - 2];
	double b = R_mat[0][n - 1];
	double X_var;
	double Y_var;
	double intermed[4][4];
	for (int i = 0; i < n; i++) {
		for (int j = (n - 1); j > i; j--) {
			a = R_mat[j - 1][i];
			b = R_mat[j][i];
			X_var = a / (sqrt(a * a + b * b));
			Y_var = -b / (sqrt(a * a + b * b));
			Gn[j][j] = X_var;
			Gn[j][j - 1] = Y_var;
			Gn[j - 1][j] = -Y_var;
			Gn[j - 1][j - 1] = X_var;
			matrix_mult(Gn, R_mat, intermed);
			AasissignB(intermed, R_mat);
			matrix_mult(Gn, Q, intermed);
			AasissignB(intermed, Q);
			for (int ident = 0; ident < n; ident++) {
				for (int ident2 = 0; ident2 < n; ident2++) {
					if (ident == ident2)
						Gn[ident][ident2] = 1;
					else
						Gn[ident][ident2] = 0;
				}
			}
			iteration += 1;
		}
	}
	double qtb[4];
	matrix_vect(Q, b_vect, qtb);
	double x4_out = qtb[3] / R_mat[3][3];
	double x3_out = (qtb[2] - x4_out * R_mat[2][3]) / R_mat[2][2];
	double x2_out = (qtb[1] - x3_out * R_mat[1][2] - x4_out * R_mat[1][3]) / R_mat[1][1];
	double x1_out = (qtb[0] - x2_out * R_mat[0][1] - x3_out * R_mat[0][2] - x4_out * R_mat[0][3]) / R_mat[0][0];
	//double x_sw_out[4] = { x1_out, x2_out,x3_out , x4_out };

}


double b1_sw_t[4] = { 0.2, 0.1, 0.8, 0.4 };
double a1_sw_t[4][4] =
{ {0.1, 0.1, 0.4, 0.3},
{ 0.2, 0.8, 0.6, 0.5},
{ 0.9, 0.1, 0.3, 0.2},
{ 0.3, 0.1, 0.4, 0.6} };

FIXED_TYPE b_vect1[4] = { 0.2, 0.1, 0.8, 0.4 };
FIXED_TYPE in_mat_a1[4][4] =
{ {0.1, 0.1, 0.4, 0.3},
{ 0.2, 0.8, 0.6, 0.5},
{ 0.9, 0.1, 0.3, 0.2},
{ 0.3, 0.1, 0.4, 0.6} };
double b1_sw[4] = { 0.2, 0.1, 0.8, 0.4 };
double a1_sw[4][4] =
{ {0.1, 0.1, 0.4, 0.3},
{ 0.2, 0.8, 0.6, 0.5},
{ 0.9, 0.1, 0.3, 0.2},
{ 0.3, 0.1, 0.4, 0.6} };

FIXED_TYPE b_vect2[4] = { 0.4,    0.2,    0.1,    0.6 };
FIXED_TYPE in_mat_a2[4][4] =
{ {0.6900, 0.5054, 0.5914, 0.5547},
{0.3401, 0.8438, 0.0687, 0.4099},
{0.3784, 0.2577, 0.2073, 0.6262},
{0.8799, 0.3194, 0.9805, 0.0850}
};

double b2_sw[4] = { 0.4,    0.2,    0.1,    0.6 };
double a2_sw[4][4] =
{ {0.6900, 0.5054, 0.5914, 0.5547},
{0.3401, 0.8438, 0.0687, 0.4099},
{0.3784, 0.2577, 0.2073, 0.6262},
{0.8799, 0.3194, 0.9805, 0.0850}
};

double b2_sw_t[4] = { 0.4,    0.2,    0.1,    0.6 };
double a2_sw_t[4][4] =
{ {0.6900, 0.5054, 0.5914, 0.5547},
{0.3401, 0.8438, 0.0687, 0.4099},
{0.3784, 0.2577, 0.2073, 0.6262},
{0.8799, 0.3194, 0.9805, 0.0850}
};

FIXED_TYPE b_vect3[4] = { 0.3384,    0.8989,    0.7795,    0.7040 };
FIXED_TYPE in_mat_a3[4][4] =
{ {0.1845, 0.7026, 0.7124, 0.6811},
 {0.6496, 0.9529, 0.7813, 0.9637},
 {0.1345, 0.5616, 0.1008, 0.9517},
 {0.9629, 0.2118, 0.8349, 0.4713}
};

double b3_sw[4] = { 0.3384,    0.8989,    0.7795,    0.7040 };
double a3_sw[4][4] =
{ {0.1845, 0.7026, 0.7124, 0.6811},
 {0.6496, 0.9529, 0.7813, 0.9637},
 {0.1345, 0.5616, 0.1008, 0.9517},
 {0.9629, 0.2118, 0.8349, 0.4713}
};

double b3_sw_t[4] = { 0.3384,    0.8989,    0.7795,    0.7040 };
double a3_sw_t[4][4] =
{ {0.1845, 0.7026, 0.7124, 0.6811},
 {0.6496, 0.9529, 0.7813, 0.9637},
 {0.1345, 0.5616, 0.1008, 0.9517},
 {0.9629, 0.2118, 0.8349, 0.4713}
};



unsigned long long tt;
int tt_print;
double tt_seconds, pl_time, ps_time, speedup;
XTime start_time_co;
XTime stop_time_co;


unsigned long long tt_sw;
int tt_print_sw;
double tt_seconds_sw, pl_time_sw, ps_time_sw, speedup_sw;
XTime start_time_co_sw;
XTime stop_time_co_sw;





int main()
{
	//software
	sw_des(a3_sw, b3_sw);
	sw_des(a2_sw, b2_sw);
	sw_des(a1_sw, b1_sw);

	cout << "--- Start of Hardware ---" << endl;
	//hardware
	hardware_des(in_mat_a3, b_vect3);
	hardware_des(in_mat_a2, b_vect2);
	hardware_des(in_mat_a1, b_vect1);
	hardware_des(in_mat_a2, b_vect2);
	//time counts
	XTime_GetTime(&start_time_co_sw);
	sw_des_time(a3_sw_t, b3_sw_t);
	sw_des_time(a2_sw_t, b2_sw_t);
	sw_des_time(a1_sw_t, b1_sw_t);
	XTime_GetTime(&stop_time_co_sw);

	XTime_GetTime(&start_time_co);
	hardware_des_time(in_mat_a3, b_vect3);
	hardware_des_time(in_mat_a2, b_vect2);
	hardware_des_time(in_mat_a1, b_vect1);
	XTime_GetTime(&stop_time_co);



	tt = stop_time_co - start_time_co;
	tt_print = (unsigned)tt;
	cout << "Done, Total time steps HARDWARE from start to finish = " << tt_print << endl;
	tt_seconds = COUNTS_PER_SECOND;
	cout << "Cycle counts per second for HARDWARE = " << tt_seconds << endl;
	pl_time = (float)tt_print / tt_seconds;
	cout << "Time in seconds for PL hardware add = times steps / COUNTS_PER_SECOND = " << pl_time << endl;

	tt_sw = stop_time_co_sw - start_time_co_sw;
	tt_print_sw = (unsigned)tt_sw;
	cout << "Done, Total time steps SOFTWARE from start to finish = " << tt_print_sw << endl;

	tt_seconds_sw = COUNTS_PER_SECOND;
	cout << "Cycle counts per second for SOFTWARE = " << tt_seconds_sw << endl;
	pl_time_sw = (float)tt_print_sw / tt_seconds_sw;
	cout << "Time in seconds for PL hardware add = times steps / COUNTS_PER_SECOND = " << pl_time_sw << endl;


	return 0;
}








