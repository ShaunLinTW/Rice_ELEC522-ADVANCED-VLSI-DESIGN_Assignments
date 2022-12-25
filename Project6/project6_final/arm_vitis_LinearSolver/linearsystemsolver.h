#ifndef LINEARSYSTEMSOLVER_H
#define LINEARSYSTEMSOLVER_H

#include "ap_fixed.h"

typedef unsigned int UINTYPE_12;
typedef ap_fixed<16,3> THETA_TYPE;
const int NUM_ITERATIONS = 64;
const int NUM_FACTORS = 7;

static THETA_TYPE pi = 3.141592653589793;

/*--------------------------------------------------------------------------------------------------
cordic function:
	Input:
		THETA_TYPE x_in		 : 	input vector x value
		THETA_TYPE y_in		 : 	input vector y value
		THETA_TYPE theta_in	 :	input theta angle (should be in range [-PI, PI])
		THETA_TYPE &x_out	 :	output x value after cordic
		THETA_TYPE &y_out	 :	output y value after cordic
		THETA_TYPE &theta_out:	output theta after cordic
		bool modes			 :	if models = 0 -> COS_SIN mode / if models = 1 -> ARCTAN mode"
--------------------------------------------------------------------------------------------------*/
void LinearSolver(THETA_TYPE A[4][4], THETA_TYPE b[4], THETA_TYPE x[4]);
void qr_decomposition(THETA_TYPE A[4][4], THETA_TYPE QT[4][4],THETA_TYPE R[4][4]);
void cordic(bool modes, THETA_TYPE x_in, THETA_TYPE y_in, THETA_TYPE theta_in, THETA_TYPE &x_out, THETA_TYPE &y_out, THETA_TYPE &theta_out, short done);

#endif
