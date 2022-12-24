#include "cordic.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TB_ITERATIONS 1000

void software_value(CORDIC_ANG_TYPE angle, CORDIC_MAG_TYPE *cos_val, CORDIC_MAG_TYPE *sin_val){
	*cos_val = (CORDIC_MAG_TYPE)cos((float)angle);
	*sin_val = (CORDIC_MAG_TYPE)sin((float)angle);
}


float compare(CORDIC_ANG_TYPE desired_angle, float threshold, float *external_error){
	CORDIC_MAG_TYPE hw_sine;
	CORDIC_MAG_TYPE hw_cosine;

	CORDIC_MAG_TYPE sw_sine;
	CORDIC_MAG_TYPE sw_cosine;

	//desired_angle = CORDIC_PI/4;
	float error = 0;
	//float threshold = 1E-5;

	circular_cordic(desired_angle, &hw_cosine, &hw_sine);
	software_value(desired_angle, &sw_cosine, &sw_sine);

	error += (float)((hw_cosine - sw_cosine)*(hw_cosine - sw_cosine));
	error += (float)((hw_sine - sw_sine)*(hw_sine - sw_sine));

	if(external_error != nullptr)
		*external_error += error;

	if(error > threshold){
		printf("Iteration Error: %0f\n", error);
		printf("Angle: %010f\n", (float)desired_angle);
		printf("HW COS: %010f\tHW SIN:%010f\n",(float)hw_cosine, (float)hw_sine);
		printf("SW COS: %010f\tSW SIN:%010f\n",(float)sw_cosine, (float)sw_sine);

		return 1;
	}
	else
		return 0;
}

int main(int argc, char *argv[]){

	printf("TB: %s\t given: %d params\n", argv[0], argc);
	
	CORDIC_ANG_TYPE desired_angle = CORDIC_PI/16; //CORDIC_PI/4;
	CORDIC_ANG_TYPE angle_step = (CORDIC_PI - desired_angle)/(4*TB_ITERATIONS);

	int error_count = 0;
	float error_total = 0;

	for(int i = 0; i < TB_ITERATIONS; i ++){
		error_count += compare(desired_angle, 1e-3, &error_total);
		desired_angle += angle_step;
		//printf("Error: %.0f.\n", error_count);
	}

	printf("Total Error Amount: %f\n", error_total);
	printf("Total Error Count: %d\n", error_count);

	return error_count;

}
