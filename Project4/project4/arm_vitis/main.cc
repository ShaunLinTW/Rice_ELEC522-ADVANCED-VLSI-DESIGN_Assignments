#include <cmath>
#include <iostream>
#include "xcordic.h"
#include "ap_fixed.h"
#include "cordic.h"
XCordic Cordic;
#include "xparameters.h"
#include "xtime_l.h"
#include "xscugic.h"

using namespace std;

typedef ap_fixed<16,4> FIXED_TYPE;

int get_int_reinterpret(FIXED_TYPE x) {
	return *(reinterpret_cast<short *>(&x));
}

FIXED_TYPE get_fixed_reinterpret(int x) {
	return *(reinterpret_cast<FIXED_TYPE *>(&x));
}
#define pi 3.1415926

int main()
{
	cout << "--- Start of the Program ---" << endl;

	FIXED_TYPE modes_in = 1;
	FIXED_TYPE x_in = 1.0;
	FIXED_TYPE y_in = 0.0;
	FIXED_TYPE theta_in = (THETA_TYPE) (45.0 * pi / 180 ); //test for 45 degree

	unsigned int modes_in_u32, x_u32, y_u32, theta_u32, x_out_u32, y_out_u32, theta_out_u32;
	int done_out = 0;
	THETA_TYPE x_out, y_out, theta_out;

// models = 0 -> COS_SIN mode
	modes_in_u32 = 0;
	x_u32 = get_int_reinterpret(x_in);
	y_u32 = get_int_reinterpret(y_in);
	theta_u32 = get_int_reinterpret(theta_in);
	cout << "Initialized for Software simulation: " << "modes=" << modes_in_u32 << ", " << "x=" << x_u32 << ", " << "y=" << y_u32 << ", " << "theta=" << theta_u32  << endl;
	XCordic_Initialize(&Cordic, 0);
	XCordic_Set_modes(&Cordic, modes_in_u32);
	XCordic_Set_x_in(&Cordic, x_u32);
	XCordic_Set_y_in(&Cordic, y_u32);
	XCordic_Set_theta_in(&Cordic, theta_u32);
	XCordic_Start(&Cordic);
	while (!XCordic_IsReady(&Cordic));
	done_out = XCordic_Get_done(&Cordic);
	x_out_u32 = XCordic_Get_x_out(&Cordic);
	y_out_u32 = XCordic_Get_y_out(&Cordic);
	theta_out_u32 = XCordic_Get_theta_out(&Cordic);
	cout << "Done signal from ARM hardware = " << done_out << endl;
	x_out = get_fixed_reinterpret(x_out_u32);
	y_out = get_fixed_reinterpret(y_out_u32);
	cout << "Hardware result after ARM calculation (COS_SIN modes): " << "x_out =" << x_out_u << ", " << "y_out=" << y_out_u << ", " << "theta_out =" << theta_out_u32 << endl;

//-----------------------------------------------------------------------------------------------------------------

	FIXED_TYPE modes_in = 1;
	FIXED_TYPE x_in = 0.258973;
	FIXED_TYPE y_in = -0.965885;
	FIXED_TYPE theta_in = (THETA_TYPE) (-75.0 * pi / 180 ); //test for -75 degree

// models = 1 -> ARCTAN mode
	modes_in_u32 = 1;
	x_u32 = get_int_reinterpret(x_in);
	y_u32 = get_int_reinterpret(y_in);
	theta_u32 = get_int_reinterpret(theta_in);
	cout << "Initialized for Software simulation: " << "modes=" << modes_in_u32 << ", " << "x=" << x_u32 << ", " << "y=" << y_u32 << ", " << "theta=" << theta_u32  << endl;
	XCordic_Initialize(&Cordic, 0);
	XCordic_Set_modes_r(&Cordic, modes_in_u32);
	XCordic_Set_x_in(&Cordic, x_u32);
	XCordic_Set_y_in(&Cordic, y_u32);
	XCordic_Set_theta_in(&Cordic, theta_u32);
	XCordic_Start(&Cordic);
	while (!XCordic_IsReady(&Cordic));
	done_out = XCordic_Get_done(&Cordic);
	x_out_u32 = XCordic_Get_x_out(&Cordic);
	y_out_u32 = XCordic_Get_y_out(&Cordic);
	theta_out_u32 = XCordic_Get_theta_out(&Cordic);
	cout << "Done signal from ARM hardware = " << done_out << endl;
	theta_out = get_fixed_reinterpret(theta_out_u32);
	cout << "Hardware result after ARM calculation (ARCTAN modes): " << "x_out =" << x_out_u << ", " << "y_out=" << y_out_u << ", " << "theta_out =" << theta_out_u32 << endl;

    cout << "--- End of the Program ---" << endl;

	return 0;
}
