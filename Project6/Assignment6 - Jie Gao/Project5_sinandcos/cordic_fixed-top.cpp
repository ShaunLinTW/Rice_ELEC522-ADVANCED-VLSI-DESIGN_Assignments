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
#include"cordic.h"
#include <stdio.h>
#include <stdlib.h>
#include "math.h"
#include <cmath>

int main()
{	


	COS_SIN_TYPE s;			//sine
	COS_SIN_TYPE c;			//cos
	THETA_TYPE angle; 		//radian versuin of degree

	COS_SIN_TYPE x;			//x
	COS_SIN_TYPE y;			//y
	THETA_TYPE R;         // R
	THETA_TYPE arctan;
	COS_SIN_TYPE x1;
	COS_SIN_TYPE y1;
	THETA_TYPE theta1;

	for(int a = 0; a < 90;a++){
	theta1 = COS_SIN_TYPE((a)*M_PI/180.0);
//	x = (COS_SIN_TYPE)cos(a*M_PI/180);
//	y = (COS_SIN_TYPE)sin(a*M_PI/180);
	x = (COS_SIN_TYPE)3;
	y = (COS_SIN_TYPE)4;
//	theta1 = (COS_SIN_TYPE)1;
	x1 = (COS_SIN_TYPE)1;
	y1 = (COS_SIN_TYPE)0;
//	cordic(angle,x,y,s,c,atan,R);
//	printf("a = %d degree, atan = %f, cos = %f, correct cos = %f, sin = %f,  correct sin = %f, R = %f \n, ",a,((double)atan)*180/M_PI,(double)c,cos(a*M_PI/180),(double)s,sin(a*M_PI/180),(double)R);

	sin_cos(theta1,x1,y1,s,c);
//	printf("x = %f, y = %f, atan = %f, R = %f \n, ",(double)x,(double)y,(double)arctan,(double)R);
	printf("theta = %f, x1 = %f, y1 = %f, sin = %f,cos = %f \n,",(double)theta1,(double)x1,(double)y1,(double)s,(double)c);
	}


	return 0;
}


