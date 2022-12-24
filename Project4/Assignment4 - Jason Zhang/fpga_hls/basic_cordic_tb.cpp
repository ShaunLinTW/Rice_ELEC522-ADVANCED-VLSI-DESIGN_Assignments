/*
This is traditional CORDIC computation of sine and cosine.
The current code is based on [FXT: cordic-circ-demo.cc]
Correctly calculates cos and sine between 0-90 degrees (0-100).

INPUT:
	double theta: Input angle
	long n: Number of iterations.
OUTPUT:
	double &s: Reference to the sine part
	double &c: Reference to the cos part

	error_sin= [abs(s-zs)/zs]*100;
	error_cos= [abs(c-zc)/zc]*100;
	Total_Error_Sin = sum(error_sin)
	Total_error_Cos = sum(error_cos)

*/
#include <math.h>
#include"basic_cordic.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

#define M_PI 3.1415926536897932384626
#define NUM_DEGREE 90

typedef ap_fixed<16, 3> COS_SIN_TYPE;
typedef ap_fixed<16, 3> THETA_TYPE;

double abs_double(double var){
	if ( var < 0)
	var = -var;
	return var;
}

// mode = 1: sin/cos
// mode = 0: arctan

int main(int argc, char **argv)
{
	COS_SIN_TYPE s;			//sine
	COS_SIN_TYPE c;			//cos
	THETA_TYPE radian; 		//radian versuin of degree
	THETA_TYPE arctanRes;

	//zs=sin, zc=cos using math.h in VivadoHLS
	double zs, zc; 			// sine and cos values calculated from math.

	//Error checking
	double Total_Error_Sin=0.0;
	double Total_error_Cos=0.0;
	double error_sin=0.0, error_cos=0.0;
	bool mode = true;

	//init value
	COS_SIN_TYPE initS = 0;
	COS_SIN_TYPE initC = 1;

	//testing sin/cos mode
	int count = 0;
	for(int i=1; i<=NUM_DEGREE; i+=15) {
			count++;
			radian = i * M_PI/180;
			zs = sin((double)radian);
			zc = cos((double)radian);
//			void cordic(data_t& x, data_t& y, data_t& theta, data_t&c, data_t&s, data_t&arctan, bool& mode);
			cordic(initC, initS, radian, c, s, arctanRes, mode);
			printf("CORDIC sin=%f, cos=%f\n", (double)s, (double)c);
//
			error_sin=(abs_double((double)s-zs)/zs);
			error_cos=(abs_double((double)c-zc)/zc);
			Total_Error_Sin=Total_Error_Sin+error_sin;
			Total_error_Cos=Total_error_Cos+error_cos;
			printf("degree=%d, radian=%f,  sin=%f, cos=%f\n", i, (double)radian, (double)zs, (double)zc);
			printf("\n");
	}
	printf ("Total_Error_Sin=%f, Total_error_Cos=%f, \n", Total_Error_Sin/count, Total_error_Cos/count);

	THETA_TYPE initT = 0;
	double Total_error_arctan=0.0;
	double error_arctan=0.0;
	count = 0;
	//testing arctan mode
	mode = false;
	for(int i=1; i<=NUM_DEGREE; i+=15) {
		count++;
		radian = i * M_PI/180;
		data_t arc_zs = (data_t)sin((double)radian);
		data_t arc_zc = (data_t)cos((double)radian);
		printf("degree=%d, radian=%f,  sin=%f, cos=%f\n", i, (double)radian, (double)arc_zs, (double)arc_zc);
		cordic(arc_zc, arc_zs, initT, c, s, arctanRes, mode);
		printf("CORDIC radian=%f, sin=%f, cos=%f\n",(double)arctanRes, (double)s, (double)c);
		error_arctan=(abs_double((double)radian-(double)arctanRes)/(double)radian);
		Total_error_arctan=Total_error_arctan+error_arctan;
		printf("\n");
	}
	printf("Total_Error_ArcTan=%f, \n", Total_error_arctan/count);
	return 0;
}
