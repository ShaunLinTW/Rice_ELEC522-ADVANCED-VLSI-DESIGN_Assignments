
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
//#include "t_fixed.h"
#include "cordic.h"

// .h file from export to IP Creator from VitisHLS. This file is in the repository added to Vitis
// It will be copied from the drivers folder to the local in my example at
// C:\ELEC522\cavallar\Tree_Fixed_HLS_Vitis\Vitis\design_1_wrapper\ps7_cortex9_0\standalone_ps7_c\include
//#include "xt_fixed.h"
#include "xcordic.h"



// Add the include path C:\Xilinx\Vitis_HLS\2021.1\include to Vitis project properties
// Add this, right click on the project name to access C/C++ Build Settings then C/C++ General
// Finally add path to Paths and Symbols, include directory
// For the c++ file for the fixed point data type
#include "ap_fixed.h"

// IMPORTANT HLS t_fixed HW instance - Needed pointer - see the xt_fixed.h file
//XT_fixed T_fixed;
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
	//inputs
	COS_SIN_TYPE x;
	COS_SIN_TYPE y;
	THETA_TYPE theta;
	bool state;
	//outputs
	COS_SIN_TYPE c;
	COS_SIN_TYPE s;
	COS_SIN_TYPE t;
	//	FIXED_TYPE a_in = 1.2;

	// values for sending over AXI bus to programmable logic (PL)
	signed int state_u32, theta_u32, x_u32, y_u32, s_out_u32, c_out_u32, t_out_u32;
	//void cordic(bool state, THETA_TYPE theta, COS_SIN_TYPE x, COS_SIN_TYPE y, COS_SIN_TYPE &s, COS_SIN_TYPE &c, THETA_TYPE_in &t);

	//sin/cos mode
	cout  << "--------------------Rotation MODE--------------------" <<endl;

	x = 1; 	y = 0; 	state = true; 	int angle = 0; theta = angle*M_PI/180;
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
    c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	x = 1; 	y = 0; 	state = true; 	angle = 30; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
    do {     t_out_u32 = XCordic_Get_t(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);    c_out_u32 = XCordic_Get_c(&Cordic);    t_out_u32 = XCordic_Get_t(&Cordic);}
    while (!XCordic_IsReady(&Cordic));     s = get_fixed_reinterpret(s_out_u32);  s = get_fixed_reinterpret(s_out_u32); 	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;


	x = 1; 	y = 0; 	state = true; 	 angle = 45; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
    do {    t_out_u32 = XCordic_Get_t(&Cordic);  s_out_u32 = XCordic_Get_s(&Cordic);    c_out_u32 = XCordic_Get_c(&Cordic);    t_out_u32 = XCordic_Get_t(&Cordic);}
    while (!XCordic_IsReady(&Cordic));     s = get_fixed_reinterpret(s_out_u32); 	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	x = 1; 	y = 0; 	state = true; 	 angle = 60; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
    do {  t_out_u32 = XCordic_Get_t(&Cordic);   s_out_u32 = XCordic_Get_s(&Cordic);    c_out_u32 = XCordic_Get_c(&Cordic);    t_out_u32 = XCordic_Get_t(&Cordic);}
    while (!XCordic_IsReady(&Cordic));     s = get_fixed_reinterpret(s_out_u32); 	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	x = 1; 	y = 0; 	state = true; 	 angle = 75; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
    do {   t_out_u32 = XCordic_Get_t(&Cordic);  s_out_u32 = XCordic_Get_s(&Cordic);    c_out_u32 = XCordic_Get_c(&Cordic);    t_out_u32 = XCordic_Get_t(&Cordic);}
    while (!XCordic_IsReady(&Cordic));
    s = get_fixed_reinterpret(s_out_u32); 	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	x = 1; 	y = 0; 	state = true; 	 angle = 90; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
    do {   t_out_u32 = XCordic_Get_t(&Cordic);  s_out_u32 = XCordic_Get_s(&Cordic);    c_out_u32 = XCordic_Get_c(&Cordic);    t_out_u32 = XCordic_Get_t(&Cordic);}
    while (!XCordic_IsReady(&Cordic));     s = get_fixed_reinterpret(s_out_u32); 	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;



	cout  << "--------------------ARCTAN MODE--------------------" <<endl;
	//arctanmode


	y = -1; 	x = 0; 	state = false;  angle = -90; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);  t_out_u32 = XCordic_Get_t(&Cordic);    }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	y = -0.865967; 	x = 00.500000; 	state = false;  angle = -60; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);  t_out_u32 = XCordic_Get_t(&Cordic);    }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	x = 0.706909; 	y = -0.706909; 	state = false;  angle = -45; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);  t_out_u32 = XCordic_Get_t(&Cordic);    }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;



	x = .96582; 	y = -0.25879; 	state = false;  angle = -15; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);   t_out_u32 = XCordic_Get_t(&Cordic);   }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;



	x = 1; 	y = 0; 	state = false;  angle = 0; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic); t_out_u32 = XCordic_Get_t(&Cordic);     }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	x = .96582; 	y = 0.25879; 	state = false;  angle = 15; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);   t_out_u32 = XCordic_Get_t(&Cordic);   }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;


	x = 0.865967; 	y = 00.500000; 	state = false;  angle = 30; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);  t_out_u32 = XCordic_Get_t(&Cordic);    }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;



	x = 0.706909; 	y = 0.706909; 	state = false;  angle = 45; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);  t_out_u32 = XCordic_Get_t(&Cordic);    }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;


	y = 0.865967; 	x = 00.500000; 	state = false;  angle = 60; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);  t_out_u32 = XCordic_Get_t(&Cordic);    }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	y = .96582; 	x = 0.25879; 	state = false;  angle = 75; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);   t_out_u32 = XCordic_Get_t(&Cordic);   }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;




	y = 1; 	x = 0; 	state = false;  angle = 90; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic); t_out_u32 = XCordic_Get_t(&Cordic);     }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;





	return 0;
}




















