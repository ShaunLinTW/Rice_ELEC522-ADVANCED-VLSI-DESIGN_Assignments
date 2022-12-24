#include "cordic.h"

void cordic(FIXED initial_x, FIXED initial_y, FIXED *final_x, FIXED *final_y, bool mode, FIXED mode0_theta, FIXED *mode1_theta) {
	#pragma HLS INTERFACE s_axilite port=return bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=initial_x bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=initial_y bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=final_x bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=final_y bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=mode bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=mode0_theta bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=mode1_theta bundle=HLS_TREEAD_PERIPH_BUS

	#pragma HLS PIPELINE II=32

	FIXED x = initial_x;
	FIXED y = initial_y;
	FIXED theta;

	if (mode == false) {
		theta = mode0_theta;
	}
	else {
		theta = 0;
	}

	for (int j = 0; j < NUM_ITERATIONS; j++) {
		FIXED x_shift = x >> j;
		FIXED y_shift = y >> j;
		if ((mode == false && theta >= 0) || (mode == true && y >= 0)) {
			x -= y_shift;
			y += x_shift;
			theta -= CORDIC_ANGLES[j];		cout << theta << endl;
		}
		else {
			x += y_shift;
			y -= x_shift;
			theta += CORDIC_ANGLES[j];		cout << theta << endl;
		}
	}

	for (int i = 0; i < NUM_SCALE_ITERATIONS; i++) {
		x += (x >> CORDIC_SCALE_J[i]);
		y += (y >> CORDIC_SCALE_J[i]);
	}

	*final_x = x;
	*final_y = y;
	*mode1_theta = theta;
}
