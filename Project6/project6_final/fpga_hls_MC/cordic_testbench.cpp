#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "cordic.h"

using namespace std;

#define PI 3.1415926

int main(int argc, char **argv)
{
	THETA_TYPE x_in, y_in, theta_in, x_out, y_out, theta_out, len_out;
	THETA_TYPE R_in, QTb_in, results;
	float cos_z, sin_z, x_sw, y_sw, len_sw;
	bool modes = 0;
	short done, degree;

	cout << "--- Start of Testbench ---" << endl;

// ----------Test 45 degree----------
	degree = 45;
	x_in = 1;
	y_in = 0;
	theta_in = (degree * pi/180);
	R_in = 0.5;
	QTb_in = 0.25;
	cos_z = cos((float)theta_in);
	sin_z = sin((float)theta_in);
	x_sw = cos_z * (float)x_in - sin_z * (float)y_in;
	y_sw = sin_z * (float)x_in + cos_z * (float)y_in;
	len_sw = sqrt(float(pow(x_sw, 2) + pow(y_sw, 2)));

	// models = 0 -> COS_SIN mode
	modes = 0;
	printf("Expected cordic COS = %f, SIN = %f\n", (float)x_sw, (float)y_sw);
	cordic(modes, x_in, y_in, theta_in, x_out, y_out, theta_out, done, R_in, QTb_in, results);
	printf("After cordic COS_out = %f, SIN_out = %f\n\n", (float)x_out, (float)y_out);

	// models = 1 -> ARCTAN mode
	modes = 1;
	printf("Expected cordic length = %f, theta(in degree) = %f\n", (float)len_sw, (float)degree);
	cordic(modes, x_sw, y_sw, 0, len_out, y_out, theta_out, done, R_in, QTb_in, results);
	printf("After cordic length_out = %f, theta_out(in degree) = %f\n\n", (float)len_out, (float)theta_out/PI*180);

// ----------Test -75 degree----------
	degree = -75;
	x_in = 1;
	y_in = 0;
	theta_in = (degree * pi/180);
	cos_z = cos((float)theta_in);
	sin_z = sin((float)theta_in);
	x_sw = cos_z * (float)x_in - sin_z * (float)y_in;
	y_sw = sin_z * (float)x_in + cos_z * (float)y_in;
	len_sw = sqrt(float(pow(x_sw, 2) + pow(y_sw, 2)));

	// models = 0 -> COS_SIN mode
	modes = 0;
	printf("Expected cordic COS = %f, SIN = %f\n", (float)x_sw, (float)y_sw);
	cordic(modes, x_in, y_in, theta_in, x_out, y_out, theta_out, done, R_in, QTb_in, results);
	printf("After cordic COS_out = %f, SIN_out = %f\n\n", (float)x_out, (float)y_out);

	// models = 1 -> ARCTAN mode
	modes = 1;
	printf("Expected cordic length = %f, theta(in degree) = %f\n", (float)len_sw, (float)degree);
	cordic(modes, x_sw, y_sw, 0, len_out, y_out, theta_out, done, R_in, QTb_in, results);
	printf("After cordic length_out = %f, theta_out(in degree) = %f\n\n", (float)len_out, (float)theta_out/PI*180);

	cout << "QTb/R=" << results << endl;

	cout << "--- End of Testbench ---" << endl;

	return 0;
}
