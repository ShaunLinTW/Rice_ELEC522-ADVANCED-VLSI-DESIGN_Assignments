#include "cordic.h"

void circular_cordic
(CORDIC_ANG_TYPE angle, 
CORDIC_MAG_TYPE *cosine, 
CORDIC_MAG_TYPE *sine){

	CORDIC_ANG_TYPE current_angle = 0;
	
	CORDIC_MAG_TYPE inter_cosine	= CORIDC_INV_K;
	CORDIC_MAG_TYPE inter_sine		= 0;
	
	CORD_LOOP:for(int i = 0; i < CORDIC_ITERATIONS; i ++){
#pragma HLS PIPELINE
		*cosine = current_angle < angle ? 
		inter_cosine - (inter_sine >> i) : inter_cosine + (inter_sine >> i);
		
		*sine = current_angle < angle ? 
		inter_sine + (inter_cosine >> i) : inter_sine - (inter_cosine >> i);

		inter_cosine = *cosine;
		inter_sine = *sine;
		
		current_angle = current_angle < angle ? 
		current_angle + Cordic_Rotations[i] : current_angle - Cordic_Rotations[i];
	}
}
