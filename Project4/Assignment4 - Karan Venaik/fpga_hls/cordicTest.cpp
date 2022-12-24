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
#include "cordic.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;
//#define M_PI 3.1415926536897932384626

double abs_double(double var){
	if ( var < 0)
	var = -var;
	return var;
}

int main(int argc, char **argv)
{
    //FILE *fp;

	COS_SIN_TYPE s;			//sine
	COS_SIN_TYPE c;			//cos
	COS_SIN_TYPE arctan;
	COS_SIN_TYPE xValue;
	COS_SIN_TYPE yValue;
	THETA_TYPE radian; 		//radian versuin of degree

	for(int i=0; i<91; i = i+15)
	{
			radian = i*M_PI/180;
			//cordic(int cordicMode, THETA_TYPE targetAnglePhi, COS_SIN_TYPE xCartesian, COS_SIN_TYPE yCartesian, COS_SIN_TYPE &arctan, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
			cordic(false, radian, 1, 0, arctan, s, c);
			fprintf(stdout, "degree=%d, radian=%f, cos=%f, sin=%f, arctan=%f\n", i, (double)radian, (double)c, (double)s, (double)arctan);
	}

	fprintf(stdout, "\n\n\n");

	for (int y = 1; y<=3; y++)
	{
		for (int x = 1; x<=3; x++)
		{
			xValue = x*1.0;
			yValue = y*1.0;
			//cordic(int cordicMode, THETA_TYPE targetAnglePhi, COS_SIN_TYPE xCartesian, COS_SIN_TYPE yCartesian, COS_SIN_TYPE &arctan, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
			cordic(true, 0, xValue, yValue, arctan, s, c);
			fprintf(stdout, "xValue=%f, yValue=%f, radian=%f, cos=%f, sin=%f, arctan=%f\n", (double)xValue, (double)yValue, (double)radian, (double)c, (double)s, (double)arctan);
		}
	}
	return 0;
}
