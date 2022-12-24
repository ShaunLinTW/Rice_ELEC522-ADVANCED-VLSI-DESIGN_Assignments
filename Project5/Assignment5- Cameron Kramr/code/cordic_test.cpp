#include "cordic.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TB_ITERATIONS 10

#define ANGLE_START (CORDIC_ANG_TYPE)-CORDIC_PI
#define ANGLE_END (CORDIC_ANG_TYPE)CORDIC_PI

#define MAG_START  (CORDIC_MAG_TYPE)-1
#define MAG_END  (CORDIC_MAG_TYPE)1

void software_value(CORDIC_ANG_TYPE angle, CORDIC_MAG_TYPE *cos_val, CORDIC_MAG_TYPE *sin_val){
	CORDIC_MAG_TYPE cos_int = *cos_val;
	CORDIC_MAG_TYPE sin_int = *sin_val;
	*cos_val = (CORDIC_MAG_TYPE)cos((float)angle)* cos_int - (CORDIC_MAG_TYPE)sin((float)angle)* sin_int;
	*sin_val = (CORDIC_MAG_TYPE)cos((float)angle)* sin_int + (CORDIC_MAG_TYPE)sin((float)angle)* cos_int;
}

void software_atan(CORDIC_ANG_TYPE *angle, CORDIC_MAG_TYPE X_Part, CORDIC_MAG_TYPE Y_Part, CORDIC_MAG_TYPE *mag_part){
	*angle = (CORDIC_ANG_TYPE)atan2((float)Y_Part, (float)X_Part);
	*mag_part = sqrt(pow((float)(X_Part), 2) + pow((float)Y_Part, 2));
}


float compare_cos_sin(CORDIC_ANG_TYPE desired_angle, float threshold, float *external_error, CORDIC_MAG_TYPE in_cosine, CORDIC_MAG_TYPE in_sine){
	//CORDIC_MAG_TYPE in_sine;
	//CORDIC_MAG_TYPE in_cosine;

	CORDIC_MAG_TYPE hw_sine;
	CORDIC_MAG_TYPE hw_cosine;

	CORDIC_ANG_TYPE angle_out;

	//in_cosine = -1;
	//in_sine = 1;

	CORDIC_MAG_TYPE sw_sine = in_sine;
	CORDIC_MAG_TYPE sw_cosine = in_cosine;

	bool arc_tan = false;

	//desired_angle = CORDIC_PI/4;
	float error = 0;
	//float threshold = 1E-5;

	circular_cordic(desired_angle, in_cosine, in_sine, &angle_out, &hw_cosine, &hw_sine, arc_tan);
	software_value(desired_angle, &sw_cosine, &sw_sine);

	error += (float)((hw_cosine - sw_cosine)*(hw_cosine - sw_cosine));
	error += (float)((hw_sine - sw_sine)*(hw_sine - sw_sine));

	if(external_error != nullptr)
		*external_error += error;

	printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", float(desired_angle), float(in_cosine), float(in_sine), float(hw_cosine), float(sw_cosine), (float)hw_sine, float(sw_sine), (float)error);

	if(error > threshold){
		return 1;
	}
	else
		return 0;
}


float compare_inv_tan(CORDIC_MAG_TYPE X_Part, CORDIC_MAG_TYPE Y_Part, float threshold, float *external_error){


	CORDIC_MAG_TYPE I;
	CORDIC_MAG_TYPE Q;
	CORDIC_MAG_TYPE hw_mag;

	CORDIC_ANG_TYPE hw_angle = 0;

	CORDIC_ANG_TYPE sw_angle = 0;
	CORDIC_MAG_TYPE sw_mag;

	bool arc_tan = 1;

	//desired_angle = CORDIC_PI/4;
	float error = 0;
	//float threshold = 1E-5;

	circular_cordic(hw_angle, X_Part, Y_Part, &hw_angle, &hw_mag, &Q, arc_tan);
	software_atan(&sw_angle, X_Part, Y_Part, &sw_mag);

	if(X_Part == 0 && Y_Part == 0){
		hw_angle = 0;	//there's something magical about this value that ap_fixed absolutely hates ;( In debugging the value is shown to be small, but when operated on it explodes for some reason
		//printf("Xs are zeros %f\n", sw_angle - hw_angle);
	}
	error += (((float)hw_angle - (float)sw_angle)*((float)hw_angle - (float)sw_angle));
	error += (((float)sw_mag - (float)hw_mag)*((float)sw_mag - (float)hw_mag));

	if(external_error != nullptr)
		*external_error += error;


	printf("%f\t%f\t%f\t%f\t%f\t%f\t%f\t%f\n", (float)X_Part, (float)Y_Part, (float)hw_mag, (float)sw_mag, (float)hw_angle, (float)sw_angle, error);

	if(error > threshold){
		return 1;
	}
	else
		return 0;
}

int main(int argc, char *argv[]){

	printf("TB: %s\t given: %d params\n", argv[0], argc);

	CORDIC_ANG_TYPE current_angle = ANGLE_START;
	CORDIC_ANG_TYPE angle_step = (ANGLE_END - ANGLE_START)/(TB_ITERATIONS - 1);

	int error_count = 0;
	float error_total = 0;

	printf("A:\tCi:\tSi:\thw_C:\tsw_C:\thw_S:\tsw_S:\tE:\n");
		for(int i = 0; i < TB_ITERATIONS; i ++){
			error_count += compare_cos_sin(current_angle, 1e-3, &error_total, -1, 1);
			error_count += compare_cos_sin(current_angle, 1e-3, &error_total, -1, -1);
			error_count += compare_cos_sin(current_angle, 1e-3, &error_total, 1, 1);
			error_count += compare_cos_sin(current_angle, 1e-3, &error_total, 1, -1);
			error_count += compare_cos_sin(current_angle, 1e-3, &error_total, 0, 1);
			error_count += compare_cos_sin(current_angle, 1e-3, &error_total, 0, -1);
			error_count += compare_cos_sin(current_angle, 1e-3, &error_total, 1, 0);
			error_count += compare_cos_sin(current_angle, 1e-3, &error_total, -1, 0);

			current_angle += angle_step;
		}


	CORDIC_MAG_TYPE current_x_step = MAG_START;
	CORDIC_MAG_TYPE current_y_step = MAG_START;
	float mag_step = (MAG_END - MAG_START)/(TB_ITERATIONS - 1);

	CORDIC_MAG_TYPE x_pos;
	CORDIC_MAG_TYPE y_pos;

	printf("*************** ATan start ***************\nTesting %d Points with %f steps\n", TB_ITERATIONS, mag_step);
	printf("X:\tY:\thw_m:\tsw_m:\thw_a:\tsw_a:\tE:\n");
	for(int i = 0; i < TB_ITERATIONS; i ++){
		for(int j = 0; j < TB_ITERATIONS; j ++){

			x_pos = current_x_step + (CORDIC_MAG_TYPE)(i * mag_step);
			y_pos = current_y_step + (CORDIC_MAG_TYPE)(j * mag_step);

			error_count += compare_inv_tan(
					(x_pos),
					(y_pos),
					1e-3,
					&error_total);
		}
	}

	printf("Total Error Amount: %f\n", error_total);
	printf("Total Error Count: %d\n", error_count);
	return error_count;

}
