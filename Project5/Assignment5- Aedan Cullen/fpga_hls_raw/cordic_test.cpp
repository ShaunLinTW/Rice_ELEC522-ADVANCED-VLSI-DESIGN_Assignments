#include "cordic.h"

int run_mode0(FIXED initial_x, FIXED initial_y, FIXED mode0_theta) {
	FIXED final_x;
	FIXED final_y;
	bool mode = false;
	FIXED mode1_theta;

	cordic(initial_x, initial_y, &final_x, &final_y, mode, mode0_theta, &mode1_theta);

	double hw_1 = (double)final_x;
	double hw_2 = (double)final_y;
	double swcos = cos((double)mode0_theta);
	double swsin = sin((double)mode0_theta);
	double sw_1 = swcos*(double)initial_x + swsin*(double)initial_y;
	double sw_2 = -swsin*(double)initial_x + swcos*(double)initial_y;

	cout << "CORDIC core results for sin/cos:" << endl;
	cout << "cos(" << mode0_theta << ") = " << hw_1 << endl;
	cout << "sin(" << mode0_theta << ") = " << hw_2 << endl;
	cout << "Software results for sin/cos:" << endl;
	cout << "cos(" << mode0_theta << ") = " << sw_1 << endl;
	cout << "sin(" << mode0_theta << ") = " << sw_2 << endl;
	if (abs(sw_1 - hw_1) < 0.01 && abs(sw_2 - hw_2) < 0.01) {
		cout << "CORDIC core and software results match" << endl << endl;
		return 0;
	}
	else {
		cout << "CORDIC core and software results DO NOT MATCH!" << endl << endl;
		return 1;
	}
}

int run_mode1(FIXED initial_x, FIXED initial_y) {
	FIXED final_x;
	FIXED final_y;
	bool mode = true;
	FIXED mode1_theta;

	cordic(initial_x, initial_y, &final_x, &final_y, mode, 0, &mode1_theta);

	double hw_1 = (double)mode1_theta;
	double sw_1 = atan((double)initial_y / (double)initial_x);

	cout << "CORDIC core results for atan2:" << endl;
	cout << "atan2(" << initial_y << ", " << initial_x << ") = " << hw_1 << endl;
	cout << "Software results for atan2:" << endl;
	cout << "atan2(" << initial_y << ", " << initial_x << ") = " << sw_1 << endl;
	if (abs(sw_1 - hw_1) < 0.01) {
		cout << "CORDIC core and software results match" << endl << endl;
		return 0;
	}
	else {
		cout << "CORDIC core and software results DO NOT MATCH!" << endl << endl;
		return 1;
	}
}

int main(int argc, char **argv) {

	int res = 0;

	res |= run_mode0(1, 0, 6*PI/12);
	res |= run_mode0(1, 0, 5*PI/12);
	res |= run_mode0(1, 0, 4*PI/12);
	res |= run_mode0(1, 0, 3*PI/12);
	res |= run_mode0(1, 0, 2*PI/12);
	res |= run_mode0(1, 0, 1*PI/12);
	res |= run_mode0(1, 0, 0);
	res |= run_mode0(1, 0, -6*PI/12);
	res |= run_mode0(1, 0, -5*PI/12);
	res |= run_mode0(1, 0, -4*PI/12);
	res |= run_mode0(1, 0, -3*PI/12);
	res |= run_mode0(1, 0, -2*PI/12);
	res |= run_mode0(1, 0, -1*PI/12);

	res |= run_mode0(-0.5, 0.5, 6*PI/12);
	res |= run_mode0(-0.25, 0.1, 5*PI/12);
	res |= run_mode0(-1.3, 0.004, 4*PI/12);
	res |= run_mode0(0.9, 0.2, 3*PI/12);
	res |= run_mode0(0.8, -0.7, 2*PI/12);
	res |= run_mode0(0.5, -1.4, 1*PI/12);
	res |= run_mode0(-0.9, -0.2, 0);
	res |= run_mode0(-0.1, -1.2, -6*PI/12);
	res |= run_mode0(1, 0, -5*PI/12);
	res |= run_mode0(-1, -1, -4*PI/12);
	res |= run_mode0(1, 1, -3*PI/12);
	res |= run_mode0(0, 1, -2*PI/12);
	res |= run_mode0(-1, -1, -1*PI/12);

	res |= run_mode1(1, 0);
	res |= run_mode1(.9, .1);
	res |= run_mode1(.8, .2);
	res |= run_mode1(.7, .3);
	res |= run_mode1(.6, .4);
	res |= run_mode1(.5, .5);
	res |= run_mode1(.4, .6);
	res |= run_mode1(.3, .7);
	res |= run_mode1(.2, .8);
	res |= run_mode1(.1, .9);
	res |= run_mode1(0, 1);

	res |= run_mode1(-1, 0);
	res |= run_mode1(-.9, .1);
	res |= run_mode1(-.8, .2);
	res |= run_mode1(-.7, .3);
	res |= run_mode1(-.6, .4);
	res |= run_mode1(-.5, .5);
	res |= run_mode1(-.4, .6);
	res |= run_mode1(-.3, .7);
	res |= run_mode1(-.2, .8);
	res |= run_mode1(-.1, .9);
	res |= run_mode1(0, 1);

	res |= run_mode1(1, 0);
	res |= run_mode1(.9, -.1);
	res |= run_mode1(.8, -.2);
	res |= run_mode1(.7, -.3);
	res |= run_mode1(.6, -.4);
	res |= run_mode1(.5, -.5);
	res |= run_mode1(.4, -.6);
	res |= run_mode1(.3, -.7);
	res |= run_mode1(.2, -.8);
	res |= run_mode1(.1, -.9);
	res |= run_mode1(0, -1);

	res |= run_mode1(-1, 0);
	res |= run_mode1(-.9, -.1);
	res |= run_mode1(-.8, -.2);
	res |= run_mode1(-.7, -.3);
	res |= run_mode1(-.6, -.4);
	res |= run_mode1(-.5, -.5);
	res |= run_mode1(-.4, -.6);
	res |= run_mode1(-.3, -.7);
	res |= run_mode1(-.2, -.8);
	res |= run_mode1(-.1, -.9);
	res |= run_mode1(0, -1);

	if (res == 0) {
		cout << endl << "All results match." << endl << endl;
	}
	else {
		cout << endl << "SOME RESULTS DO NOT MATCH." << endl << endl;
	}
}
