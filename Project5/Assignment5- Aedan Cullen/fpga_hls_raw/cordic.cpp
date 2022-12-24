#include "cordic.h"

void cordic(FIXED initial_x, FIXED initial_y, FIXED *final_x, FIXED *final_y, bool mode, FIXED mode0_theta, FIXED *mode1_theta) {
	#pragma HLS PIPELINE II=1
	#pragma HLS LATENCY MIN=20 MAX=20

	FIXED x;
	FIXED y;
	FIXED theta;

	if (mode == false) {
		x = initial_x;
		y = initial_y;
		theta = -mode0_theta;
	}
	else {
		if (initial_x < 0 && initial_y >= 0) {
			//x = initial_y;
			//y = -initial_x;
			x = -initial_x;
			y = -initial_y;
			theta = 0;//PI/2;
		}
		else if (initial_x < 0 && initial_y < 0) {
			//x = -initial_y;
			//y = initial_x;
			x = -initial_x;
			y = -initial_y;
			theta = 0;//-PI/2;
		}
		else {
			x = initial_x;
			y = initial_y;
			theta = 0;
		}
	}

	for (int j = 0; j < NUM_ITERATIONS; j++) {
		FIXED x_shift = x >> j;
		FIXED y_shift = y >> j;
		if ((mode == false && theta >= 0) || (mode == true && y < 0)) {
			x -= y_shift;
			y += x_shift;
			theta -= CORDIC_ANGLES[j];
		}
		else {
			x += y_shift;
			y -= x_shift;
			theta += CORDIC_ANGLES[j];
		}
	}

	for (int i = 0; i < NUM_SCALE_ITERATIONS; i++ ) {
		if (CORDIC_SCALE_S[i] == false) {
			x -= (x >> CORDIC_SCALE_J[i]);
			y -= (y >> CORDIC_SCALE_J[i]);
		}
		else {
			x += (x >> CORDIC_SCALE_J[i]);
			y += (y >> CORDIC_SCALE_J[i]);
		}
	}

	*final_x = x;
	*final_y = y;
	*mode1_theta = theta;
}
