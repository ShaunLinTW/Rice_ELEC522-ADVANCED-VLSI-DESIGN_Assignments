/*
 * main.cpp
 *
 *  Created on: Nov 10, 2022
 *      Author: ckk5
 */

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include "ap_fixed.h"

#include "xcircular_cordic.h"

XCircular_cordic cordic_accl;

#include "xparameters.h"
#include "xtime_l.h"

typedef  ap_fixed<16,3,AP_RND> CORDIC_MAG_TYPE;
typedef  ap_fixed<16,3,AP_RND> CORDIC_ANG_TYPE;

#define CORDIC_PI (CORDIC_ANG_TYPE) 3.14159265358979
#define CORDIC_INV_K (CORDIC_MAG_TYPE) 0.607252935103139000000

//Macros for interpreting Axi data types
int get_int_reinterpret_mag(CORDIC_MAG_TYPE x){
	return *(reinterpret_cast<short *>(&x));
}

CORDIC_MAG_TYPE get_mag_reinterpret(int x){
	return *(reinterpret_cast<CORDIC_MAG_TYPE *>(&x));
}

int get_int_reinterpret_ang(CORDIC_ANG_TYPE x){
	return *(reinterpret_cast<short *>(&x));
}

CORDIC_ANG_TYPE get_ang_reinterpret(int x){
	return *(reinterpret_cast<CORDIC_ANG_TYPE *>(&x));
}

using namespace std;

void software_value(CORDIC_ANG_TYPE angle, CORDIC_MAG_TYPE *cos_val, CORDIC_MAG_TYPE *sin_val){
	CORDIC_MAG_TYPE cos_int = *cos_val;
	CORDIC_MAG_TYPE sin_int = *sin_val;
	*cos_val = (CORDIC_MAG_TYPE)cos((float)angle)* cos_int + (CORDIC_MAG_TYPE)sin((float)angle)* sin_int;
	*sin_val = (CORDIC_MAG_TYPE)cos((float)angle)* sin_int - (CORDIC_MAG_TYPE)sin((float)angle)* cos_int;
}

void software_atan(CORDIC_ANG_TYPE *angle, CORDIC_MAG_TYPE X_Part, CORDIC_MAG_TYPE Y_Part, CORDIC_MAG_TYPE *mag_part){
	*angle = (CORDIC_ANG_TYPE)atan2((float)Y_Part, (float)X_Part);
	*mag_part = sqrt(pow((float)(X_Part), 2) + pow((float)Y_Part, 2));
}


void sw_arc_tan(
		CORDIC_ANG_TYPE Angle,
		CORDIC_MAG_TYPE In_Phase,
		CORDIC_MAG_TYPE Quadrature,
		CORDIC_ANG_TYPE *Angle_out,
		CORDIC_MAG_TYPE *Mag_out){

	software_atan(&Angle, In_Phase, Quadrature, Mag_out);

	//printf("SW atan: A: %f\tI: %f\tQ: %f\n", (float)(Angle), (float)(In_Phase), (float)(Quadrature));
	*Angle_out = Angle;
	//*Mag_out = In_Phase;
}

void sw_sin_cos(
		CORDIC_ANG_TYPE Angle,
		CORDIC_MAG_TYPE In_Phase,
		CORDIC_MAG_TYPE Quadrature,
		CORDIC_MAG_TYPE *In_Phase_out,
		CORDIC_MAG_TYPE *Quadrature_out){

	software_value(Angle, &In_Phase, &Quadrature);

	//printf("SW: A: %f\tI: %f\tQ: %f\n", (float)(Angle), (float)(In_Phase), (float)(Quadrature));

	*In_Phase_out = In_Phase;
	*Quadrature_out = Quadrature;
}

bool hw_sin_cos(
		CORDIC_ANG_TYPE Angle,
		CORDIC_MAG_TYPE In_Phase,
		CORDIC_MAG_TYPE Quadrature,
		CORDIC_MAG_TYPE *In_Phase_out,
		CORDIC_MAG_TYPE *Quadrature_out){

	unsigned int Angle_int = get_int_reinterpret_ang(Angle);
	unsigned int In_Phase_int = get_int_reinterpret_mag(In_Phase);
	unsigned int Quadrature_int = get_int_reinterpret_mag(Quadrature);


	unsigned int In_Phase_int_out = 0;
	unsigned int Quadrature_int_out = 0;

	bool arc_tan = 0;
	bool done = 0;

	XCircular_cordic_Set_angle_in(&cordic_accl, Angle_int);
	XCircular_cordic_Set_sine_In(&cordic_accl, Quadrature_int);
	XCircular_cordic_Set_cosine_In(&cordic_accl, In_Phase_int);
	XCircular_cordic_Set_arc_tan(&cordic_accl, arc_tan);
	//XCircular_cordic_Set_done(&cordic_accl, 0);

	XCircular_cordic_Start(&cordic_accl);

	int count = 0;

	do	{
		count ++;
		In_Phase_int_out = XCircular_cordic_Get_cosine_Out(&cordic_accl);
		Quadrature_int_out = XCircular_cordic_Get_sine_Out(&cordic_accl);
		XCircular_cordic_Get_angle_Out(&cordic_accl);
		XCircular_cordic_Get_done(&cordic_accl);

		done = XCircular_cordic_Get_done(&cordic_accl);
	}while(!XCircular_cordic_IsReady(&cordic_accl) && !done);

	*In_Phase_out = get_mag_reinterpret(In_Phase_int_out);
	*Quadrature_out = get_mag_reinterpret(Quadrature_int_out);

	//printf("HW: A: %f\tI: %f\tQ: %f\tWaited: %d\tDone: %d\n", (float)(Angle), (float)(*In_Phase_out), (float)(*Quadrature_out), count, done);
	return done;
}

bool hw_arc_tan(
		CORDIC_ANG_TYPE Angle,
		CORDIC_MAG_TYPE In_Phase,
		CORDIC_MAG_TYPE Quadrature,
		CORDIC_MAG_TYPE *Angle_out,
		CORDIC_MAG_TYPE *In_Phase_out){

	unsigned int Angle_int = get_int_reinterpret_ang(Angle);
	unsigned int In_Phase_int = get_int_reinterpret_mag(In_Phase);
	unsigned int Quadrature_int = get_int_reinterpret_mag(Quadrature);


	unsigned int In_Phase_int_out = 0;
	unsigned int angle_int_out = 0;

	bool arc_tan = 1;
	bool done = 0;

	//XCircular_cordic_Set_angle_in(&cordic_accl, Angle_int);
	XCircular_cordic_Set_sine_In(&cordic_accl, Quadrature_int);
	XCircular_cordic_Set_cosine_In(&cordic_accl, In_Phase_int);
	XCircular_cordic_Set_arc_tan(&cordic_accl, arc_tan);

	XCircular_cordic_Start(&cordic_accl);

	int count = 0;

	do	{
		count ++;
		In_Phase_int_out = XCircular_cordic_Get_cosine_Out(&cordic_accl);
		angle_int_out = XCircular_cordic_Get_angle_Out(&cordic_accl);

		done = XCircular_cordic_Get_done(&cordic_accl);
	}while(!XCircular_cordic_IsReady(&cordic_accl));

	*In_Phase_out = get_mag_reinterpret(In_Phase_int_out);
	*Angle_out = get_ang_reinterpret(angle_int_out);

	//printf("HW atan: A: %f\tI: %f\tQ: %f\tWaited: %d\tDone: %d\n", (float)(*Angle_out), (float)(*In_Phase_out), (float)(Quadrature), count, done);
	return done;
}

void print_inputs(CORDIC_ANG_TYPE Angle, CORDIC_MAG_TYPE Inpha, CORDIC_MAG_TYPE Quad){
	printf("%f\t%f\t%f\t",  (float)Angle, (float)Inpha, (float)Quad);
}

void report_arc_tan(CORDIC_ANG_TYPE HW_A, CORDIC_ANG_TYPE SW_A, CORDIC_MAG_TYPE HW_M, CORDIC_MAG_TYPE SW_M, float error, bool fail){
	printf("%f\t%f\t%f\t%f\t%f\t%u\n", (float)HW_A, (float)SW_A, (float)HW_M, (float)SW_M, error, (int)fail);
}
void report_sin_cos(CORDIC_MAG_TYPE HW_Ip, CORDIC_MAG_TYPE SW_Ip, CORDIC_MAG_TYPE HW_Qa, CORDIC_MAG_TYPE SW_Qa, float error, bool fail){
	printf("%f\t%f\t%f\t%f\t%f\t%u\n", (float)HW_Ip, (float)SW_Ip, (float)HW_Qa, (float)SW_Qa, error, (int)fail);
}

void test_sin_cos(int loops, float thresh){
	CORDIC_MAG_TYPE HW_Ip;
	CORDIC_MAG_TYPE HW_Qa;

	CORDIC_MAG_TYPE SW_Ip;
	CORDIC_MAG_TYPE SW_Qa;

	CORDIC_ANG_TYPE ANGLE_END = CORDIC_PI/4;
	CORDIC_ANG_TYPE ANGLE_START = -3*CORDIC_PI/4;

	CORDIC_MAG_TYPE MAG_START = -1;
	CORDIC_MAG_TYPE MAG_END = -1;

	CORDIC_MAG_TYPE mag_step = (ANGLE_END - ANGLE_START)/(loops - 1);
	CORDIC_ANG_TYPE angle_step = (ANGLE_END - ANGLE_START)/(loops - 1);


	CORDIC_MAG_TYPE In_Ip;
	CORDIC_MAG_TYPE In_Qa;
	CORDIC_ANG_TYPE In_Ang;

	float error = 0;
	int error_count = 0;

	printf("Ang \tIN IP \tIN QA \tHW IP\t SW IP\t HW QA\t SW QA\t ERROR\t FAIL\n");
	for(int i = 0; i < loops; i ++){
		for(int k = 0; k < loops; k ++){
			for(int l = 0; l < loops; l ++){

				In_Ang = ANGLE_START + angle_step*i;
				In_Ip = MAG_START + mag_step*k,
				In_Qa = MAG_START + mag_step*l,

				sw_sin_cos(In_Ang,In_Qa,In_Ip,&SW_Ip,&SW_Qa);

				hw_sin_cos(In_Ang, In_Qa, In_Ip, &HW_Ip, &HW_Qa);

				error += (float)((SW_Ip - HW_Ip)*(SW_Ip - HW_Ip));
				error += (float)((SW_Qa - HW_Qa)*(SW_Qa - HW_Qa));

				print_inputs(In_Ang, In_Ip, In_Qa);
				report_sin_cos(HW_Ip, SW_Ip, HW_Qa, SW_Qa, error, error > thresh);
				if(error > thresh)
					error_count ++;
			}
		}
	}
	printf("Total Error Count: %u\n", error_count);
	printf("Total Error Mag: %f\n", error);
}

int main()
{

	CORDIC_ANG_TYPE HW_Angle;
	CORDIC_MAG_TYPE HW_Mag;

	CORDIC_ANG_TYPE SW_Angle;
	CORDIC_MAG_TYPE SW_Mag;


	CORDIC_MAG_TYPE In_Ip = -1;
	CORDIC_MAG_TYPE In_Qa = -1;
	CORDIC_ANG_TYPE In_An = 0;

	XCircular_cordic_Initialize(&cordic_accl, 0);

	printf("Hello cordic World\n");

	//Test for sin cosine
	//test_sin_cos(1, 0.003);


	//I can't stay up anymore to turn this into a proper test. Doesn't even matter if I can't get it working anyway.
	sw_arc_tan(In_An, In_Ip, In_Qa, &SW_Angle, &SW_Mag);
	hw_arc_tan(In_An, In_Ip, In_Qa, &HW_Angle, &HW_Mag);

	float error = (float)((SW_Angle - HW_Angle)*(SW_Angle - HW_Angle));
	error += (float)((SW_Mag - HW_Mag)*(SW_Mag - HW_Mag));


	printf("IN A \tIN IP \tIn QA\t HW A\t SW A\t HW Mag\t SW Mag\t ERROR\t FAIL\n");
	print_inputs(In_An, In_Ip, In_Qa);
	report_arc_tan(HW_Angle, SW_Angle, HW_Mag, SW_Mag, error, error > 0.003);

	printf("Exiting\n");
	return 0;
}

