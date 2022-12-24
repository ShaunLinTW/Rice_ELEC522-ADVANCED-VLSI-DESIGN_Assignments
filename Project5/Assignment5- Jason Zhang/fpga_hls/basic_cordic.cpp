/*********************************************************************/
// Description:														  /
//     Your C++ implementation of CORDIC.                             /
//	   Please follow the instructions below to complete the function. /
/*********************************************************************/

#include"basic_cordic.h"
#include <iostream>

using namespace std;

void cordic(data_t& x, data_t& y, data_t& theta, data_t&c, data_t&s, data_t&arctan, bool& mode) {
#pragma HLS PIPELINE

//#pragma HLS INTERFACE s_axilite port=x bundle=HLS_TREEADD_PERIPH_BUS
//#pragma HLS INTERFACE s_axilite port=y bundle=HLS_TREEADD_PERIPH_BUS
//#pragma HLS INTERFACE s_axilite port=theta bundle=HLS_TREEADD_PERIPH_BUS
//#pragma HLS INTERFACE s_axilite port=x bundle=HLS_TREEADD_PERIPH_BUS
//#pragma HLS INTERFACE s_axilite port=y bundle=HLS_TREEADD_PERIPH_BUS
//#pragma HLS INTERFACE s_axilite port=mode bundle=HLS_TREEADD_PERIPH_BUS

	// -------- initialize variants --------
	// cur_x: x value of the rotated vector
	// cur_y: y value of the rotated vector
	// cur_z: accumulated angle
	data_t cur_x = 0;
	data_t cur_y = 0;
	data_t cur_z = 0;
	int angleCorrection = 0;

	if (mode) {
		// if we are in sin/cos mode
		// -------- Angle Correction ---------
		// make theta within [-pi/2, pi/2]
		if (theta < -piHalf || theta > piHalf) {
			if (theta < 0) {
				theta += pi;
			} else {
				theta -= pi;
			}
			angleCorrection = 1;
		}
	} else {
		// if we are in arctan mode
		// -------- Angle Correction --------
		// prerotate the vector to quadrant I or IV
		if (x < 0) {
			if (y >= 0) {
				cur_x = y;
				cur_y = -x;
				angleCorrection = 2;
			} else {
				cur_x = -y;
				cur_y = x;
				angleCorrection = 3;
			}
		}
	}
	cur_x = x;
	cur_y = y;
	cur_z = 0;

	// -------- Rotation --------
	for (int i = 0; i < 32; ++i) {
		#pragma HLS PIPELINE

		data_t next_x = (cur_y >> i);
		data_t next_y = (cur_x >> i);
		data_t next_phase =  theta_LUT[i];
		if (mode && cur_z < theta || !mode && cur_y < 0) {
			// rotate counter_clockwise
			cur_x = cur_x - next_x;
			cur_y = cur_y + next_y;
			cur_z += next_phase;
		} else {
			// rotate clockwise
			cur_x = cur_x + next_x;
			cur_y = cur_y - next_y;
			cur_z -= next_phase;
		}
	}
	printf("After Rotation: cur_x=%f, cur_y=%f, cur_z=%f\n", double(cur_x), double(cur_y), double(cur_z));
	// -------- Scaling correction --------
//	bool flip = true;
	for (int i = 0; i < 7; ++i) {
		#pragma HLS PIPELINE
		data_t next_x = cur_x >> scaling_factors[i];
		data_t next_y = cur_y >> scaling_factors[i];

		if (scaling_sign[i]) {
			// plus
			cur_x = cur_x + next_x;
			cur_y = cur_y + next_y;
		} else {
			// minus
			cur_x = cur_x - next_x;
			cur_y = cur_y - next_y;
		}
//		if (flip) {
//			cur_x = cur_x - next_x;
//			cur_y = cur_y - next_y;
//		} else {
//			cur_x = cur_x + next_x;
//			cur_y = cur_y + next_y;
//		}
//		flip = !flip;
	}
	printf("After Scaling: cur_x=%f, cur_y=%f, cur_z=%f\n", double(cur_x), double(cur_y), double(cur_z));
	printf("angle correction: %d\n", angleCorrection);
	// -------- Angle correction ---------
	arctan = -cur_z;
	c = cur_x;
	s = cur_y;
	if (angleCorrection == 1) {
		c = -cur_x;
		s = -cur_y;
	} else if (angleCorrection == 2) {
		arctan += piHalf;
	} else if (angleCorrection == 3) {
		arctan -= piHalf;
	}

	printf("return values: c=%f, s=%f, arctan=%f\n", double(c), double(s), double(arctan));
	// --------result --------
	// for sin/cos mode:
	// output: x -> rotated(x), y -> rotated(y), theta -> 0 (we dont care)
	// for arctan mode:
	// output: x -> vectorLength, y -> 0 (we dont care), theta -> arctan angle
}
