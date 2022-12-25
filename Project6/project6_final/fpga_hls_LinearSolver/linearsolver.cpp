#include <iostream>
#include "linearsolver.h"

static THETA_TYPE cordic_phase[NUM_ITERATIONS]={0.78539816339744828000,0.46364760900080609000,0.24497866312686414000,0.12435499454676144000,0.06241880999595735000,0.03123983343026827700,0.01562372862047683100,0.00781234106010111110,0.00390623013196697180,0.00195312251647881880,
												0.00097656218955931946,0.00048828121119489829,0.00024414062014936177,0.00012207031189367021,0.00006103515617420877,0.00003051757811552610,0.00001525878906131576,0.00000762939453110197,0.00000381469726560650,0.00000190734863281019,
												0.00000095367431640596,0.00000047683715820309,0.00000023841857910156,0.00000011920928955078,0.00000005960464477539,0.00000002980232238770,0.00000001490116119385,0.00000000745058059692,0.00000000372529029846,0.00000000186264514923,
												0.00000000093132257462,0.00000000046566128731,0.00000000023283064365,0.00000000011641532183,0.00000000005820766091,0.00000000002910383046,0.00000000001455191523,0.00000000000727595761,0.00000000000363797881,0.00000000000181898940,
												0.00000000000090949470,0.00000000000045474735,0.00000000000022737368,0.00000000000011368684,0.00000000000005684342,0.00000000000002842171,0.00000000000001421085,0.00000000000000710543,0.00000000000000355271,0.00000000000000177636,
												0.00000000000000088818,0.00000000000000044409,0.00000000000000022204,0.00000000000000011102,0.00000000000000005551,0.00000000000000002776,0.00000000000000001388,0.00000000000000000694,0.00000000000000000347,0.00000000000000000173,
												0.00000000000000000087,0.00000000000000000043,0.00000000000000000022,0.00000000000000000011};

static char scaling_factors[NUM_FACTORS]={1, 2, 5, 10, 16, 19, 22};

void LinearSolver(THETA_TYPE A[4][4], THETA_TYPE b[4], THETA_TYPE x[4])
{
#pragma HLS INTERFACE mode=s_axilite bundle=A_in port=A
#pragma HLS INTERFACE mode=s_axilite bundle=b_in port=b
#pragma HLS INTERFACE mode=s_axilite bundle=x_out port=x

#pragma HLS PIPELINE

    THETA_TYPE R_Temp[4][4], QT_Temp[4][4], QT[4][4], R[4][4];
    THETA_TYPE y[4];
    THETA_TYPE sum;

    qr_decomposition(A, QT_Temp, R_Temp);

    for(int i = 0; i < 4; i++){
    	for(int j = 0; j < 4; j++){
    		QT[i][j] = QT_Temp[i][j];
    		R[i][j] = R_Temp[i][j];
    	}
    }

	// y = QT*b
	for(int i = 0; i < 4; i++){
		sum = 0;
		for(int j = 0; j < 4; j++){
			sum = sum + QT[i][j] * b[j];
		}
		y[i] = sum;
	}

	// Back-substitution
	x[3] = y[3] / R[3][3];
	x[2] = (y[2] - (R[2][3] * x[3])) / R[2][2];
	x[1] = (y[1] - (R[1][2] * x[2]) - (R[1][3] * x[3])) / R[1][1];
	x[0] = (y[0] - (R[0][1] * x[1]) - (R[0][2] * x[2]) - (R[0][3] * x[3])) / R[0][0];
}

void qr_decomposition(THETA_TYPE A[4][4], THETA_TYPE QT[4][4], THETA_TYPE R[4][4])
{
	THETA_TYPE R_Temp[4][4], QT_Temp[4][4];
	THETA_TYPE theta = 0;
	THETA_TYPE x_out, y_out, theta_out;
	int done = 1;

	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			R_Temp[row][col] = A[row][col];
			QT_Temp[row][col] = 0;
		}
	}

	QT_Temp[0][0] = 1;
	QT_Temp[1][1] = 1;
	QT_Temp[2][2] = 1;
	QT_Temp[3][3] = 1;

	for(int col = 0; col < 4; col++){
		for(int row = 2; row >= col; row--){
			cordic(1, R_Temp[row][col], -R_Temp[row+1][col], theta, x_out, y_out, theta_out, done);

			R_Temp[row][col] = x_out;
			R_Temp[row+1][col] = 0;
			theta = theta_out;

			for(int i = col+1; i < 4; i++){
				cordic(0, R_Temp[row][i], R_Temp[row+1][i], theta, R_Temp[row][i], R_Temp[row+1][i], theta_out, done);
			}

			for(int i = 0; i < 4; i++){
				cordic(0, QT_Temp[row][i], QT_Temp[row+1][i], theta, QT_Temp[row][i], QT_Temp[row+1][i], theta_out, done);
			}
		}
	}
//	save QT, R matrix results
	for(int row = 0; row < 4; row++){
		for(int col = 0; col < 4; col++){
			R[row][col] = R_Temp[row][col];
			QT[row][col] = QT_Temp[row][col];
		}
	}
}

void cordic(bool modes, THETA_TYPE x_in, THETA_TYPE y_in, THETA_TYPE theta_in, THETA_TYPE &x_out, THETA_TYPE &y_out, THETA_TYPE &theta_out, short done)
{
	x_out, y_out, theta_out = 0;
	THETA_TYPE xi, yi, angle, phase;
	THETA_TYPE theta = 0;
	THETA_TYPE x_shift, y_shift = 0;
	char Quadrant = 0;

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

	//======================Choose modes===============================
	// models = 0 -> COS_SIN mode
		if(modes == 0){
			if(theta_in < -pi/2){
				angle = theta_in + pi;
				Quadrant = 2;
			}
			else if(theta_in > pi/2){
				angle = theta_in - pi;
				Quadrant = 1;
			}
			else{
				angle = theta_in;
				Quadrant = 0;
			}
			xi = x_in;
			yi = y_in;
		}

	// models = 1 -> ARCTAN mode
		if(modes == 1){
			if (x_in >=0){
				xi = x_in;
				yi = y_in;
				Quadrant = 0;
			}
			if(x_in < 0){
				if(y_in > 0){
					xi = y_in;
					yi = -x_in;
					Quadrant = 3;
				}
				else{
					xi = -y_in;
					yi = x_in;
					Quadrant = 4;
				}
			}
		}

	//====================Rotate and Scale=============================
	Rotation_function:
		for (int i = 0; i < NUM_ITERATIONS; i++){
			//2^(-i)
			phase = cordic_phase[i];
			x_shift = (yi >> i);
			y_shift = (xi >> i);
			if((modes == 0 && theta < angle) || (modes == 1 && yi < 0)){
				xi = xi - x_shift;
				yi = yi + y_shift;
				theta = theta + phase;
			}
			else{
				xi = xi + x_shift;
				yi = yi - y_shift;
				theta = theta - phase;
			}
		}

	Scale_function:
		for (int j = 0; j < NUM_FACTORS; j++){
			x_shift = (xi >> scaling_factors[j]);
			y_shift = (yi >> scaling_factors[j]);
			if(j == 0 || j == 2){
				xi = xi - x_shift;
			}
			else{
				xi = xi + x_shift;
			}
			if((j == 0 || j == 2) && (modes == 0)){
				yi = yi - y_shift;
			}
			else{
				yi = yi + y_shift;
			}
		}

	//=======================save the result===========================
		if(modes == 0){
			if(Quadrant){
				x_out = -xi;
				y_out = -yi;
			}
			else{
				x_out = xi;
				y_out = yi;
			}
			theta_out = 0;
		}

		else{
			x_out = xi;
			y_out = 0;
			theta_out = -theta;
			if(Quadrant == 3){
				theta_out = theta_out + pi/2;
			}
			if(Quadrant == 4){
				theta_out = theta_out - pi/2;
			}
		}
	done = 1;
}
