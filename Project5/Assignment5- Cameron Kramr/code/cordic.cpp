#include "cordic.h"

inline CORDIC_MAG_TYPE scale_factor_correction(CORDIC_MAG_TYPE magnitude){
	SCALE_LOOP:for(int i = 0; i < CORDIC_SCALE_SHIFTS; i ++){
#pragma HLS UNROLL
		magnitude = magnitude - (magnitude >> CORDIC_SCALE_SHIFT[i]);
	}
	return magnitude;
}

void circular_cordic
(
	CORDIC_ANG_TYPE angle_in,
	CORDIC_MAG_TYPE cosine_In,
	CORDIC_MAG_TYPE sine_In,
	CORDIC_ANG_TYPE *angle_Out,
	CORDIC_MAG_TYPE *cosine_Out,
	CORDIC_MAG_TYPE *sine_Out,
	bool		arc_tan/*,
	bool		*done*/){
	/*
#pragma HLS INTERFACE s_axilite port=return bundle=CORDIC_MOD
#pragma HLS INTERFACE s_axilite port=angle_in bundle=CORDIC_MOD
#pragma HLS INTERFACE s_axilite port=cosine_In bundle=CORDIC_MOD
#pragma HLS INTERFACE s_axilite port=sine_In bundle=CORDIC_MOD
#pragma HLS INTERFACE s_axilite port=angle_Out bundle=CORDIC_MOD
#pragma HLS INTERFACE s_axilite port=cosine_Out bundle=CORDIC_MOD
#pragma HLS INTERFACE s_axilite port=sine_Out bundle=CORDIC_MOD
#pragma HLS INTERFACE s_axilite port=arc_tan bundle=CORDIC_MOD
#pragma HLS INTERFACE s_axilite port=done bundle=CORDIC_MOD
#pragma HLS PIPELINE II=1
*/
	CORDIC_ANG_TYPE accum_angle;// = 0;
	CORDIC_ANG_TYPE input_angle = angle_in;// = 0;
	CORDIC_MAG_TYPE inter_cosine;//	= 0;//CORIDC_INV_K;
	CORDIC_MAG_TYPE inter_sine;//		= 0;
	CORDIC_MAG_TYPE new_cosine;
	CORDIC_MAG_TYPE new_sine;

	uint8_t increment = 0;

	//Inverse Tangent Setup
	if(arc_tan){
		if(cosine_In < 0){
			//Angle is located within the second or third quadrant
			if(sine_In > 0){
				accum_angle = -CORDIC_PI/2;
				inter_cosine = sine_In;
				inter_sine = -cosine_In;
			}else{
				accum_angle = CORDIC_PI/2;
				inter_cosine = -sine_In;
				inter_sine = cosine_In;
			}
		}else{
			//Angle is located within the first or fourth quadrant
			accum_angle = 0;
			inter_cosine = cosine_In;
			inter_sine = sine_In;
		}

	//Sine / Cosine Setup
	}else{
		//Configure Starting Point So target angle is within cordic range
		if(input_angle < -CORDIC_PI/2){
			accum_angle = -CORDIC_PI/2;
			inter_cosine = sine_In;
			inter_sine = -cosine_In;
		}else
		if(input_angle > CORDIC_PI/2){
			accum_angle = CORDIC_PI/2;
			inter_cosine = -sine_In;
			inter_sine = cosine_In;
		}else{
			accum_angle = 0;
			inter_cosine = cosine_In;
			inter_sine = sine_In;
		}
	}

	CORD_LOOP:for(int i = 0; i < CORDIC_ITERATIONS; i ++){
//#pragma HLS PIPELINE

		increment = arc_tan ? (uint8_t)(inter_sine < 0): uint8_t(accum_angle < input_angle);

		//Update Parameters
		//Cosine Update
		new_cosine = increment != 0 ?
		inter_cosine - (inter_sine >> i) : inter_cosine + (inter_sine >> i);
		
		//Sine Update
		new_sine = increment != 0 ?
		inter_sine + (inter_cosine >> i) : inter_sine - (inter_cosine >> i);

		//Angle Update
		accum_angle = increment != 0 ?
		accum_angle + Cordic_Rotations[i] : accum_angle - Cordic_Rotations[i];

		//Update intermediate values
		inter_cosine = new_cosine;

		inter_sine = new_sine;
	}

	//Assign Output
	*angle_Out = -accum_angle;

	*cosine_Out	= scale_factor_correction(new_cosine);
	*sine_Out	= scale_factor_correction(new_sine);
}

