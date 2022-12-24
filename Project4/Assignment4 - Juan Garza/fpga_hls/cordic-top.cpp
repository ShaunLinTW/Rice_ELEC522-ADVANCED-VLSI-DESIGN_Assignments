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
#include"cordic.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;
//#define M_PI 1.5707963267

double abs_double(double var){
	if ( var < 0)
	var = -var;
	return var;


}
int main(int argc, char **argv)
{	FILE *fp;
	COS_SIN_TYPE s;			//sine
	COS_SIN_TYPE c;			//cos
	THETA_TYPE_in t;			//cos

	THETA_TYPE radian; 		//radian versuin of degree
	bool state;
	COS_SIN_TYPE x;			//x_cord
	COS_SIN_TYPE y;			//y_cord

	//zs=sin, zc=cos using math.h in VivadoHLS
	double zs, zc; 			// sine and cos values calculated from math.

	//Error checking
	double Total_Error_Sin=0.0;
	double Total_error_Cos=0.0;
	double error_sin=0.0, error_cos=0.0;

	//fp=fopen("out.dat","w");

	for(int i=-90;i<NUM_DEGREE;i=i+15) {
			radian = i*M_PI/180;
			cordic(true, radian, 1.0, 0, s, c, t);
			zs = sin((double)radian);
			zc = cos((double)radian);
			error_sin=(abs_double((double)s-zs)/zs)*100.0;
			error_cos=(abs_double((double)c-zc)/zc)*100.0;
			Total_Error_Sin=Total_Error_Sin+error_sin;
			Total_error_Cos=Total_error_Cos+error_cos;
			fprintf(stdout, "degree=%d, radian=%f, cos=%f, sin=%f\n", i, (double)radian, (double)c, (double)s);
	}
	printf ("Total_Error_Sin=%f, Total_error_Cos=%f, \n", Total_Error_Sin, Total_error_Cos);


// x  1      0.9659 0.866  0.707  .5    0.2588
// y  0      0.2588 0.5    0.707  0.866 0.9659
	x= 0.0;    y=  -1.0; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x= 0.2588; y=  -0.9659; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x=0.5;    y= -0.866; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x= 0.707; y=  -0.707; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x= 0.866; y=  -0.5; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x= 0.9659; y=  -0.2588; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);

	x= 1.0; y= 0.0; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%d, y_in=%d, t_theta=%f\n", 1, (double)y, (double)t);

	x= 0.9659; y=  0.2588; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x= 0.866; y=  0.5; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x= 0.707; y=  0.707; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x=0.5;    y= 0.866; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x= 0.2588; y=  0.9659; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);
	x= 0.0;    y=  1.0; 	cordic(false, 0, x, y, s, c, t);
	fprintf(stdout, "x_in=%f, y_in=%f, t_theta=%f\n", (double)x, (double)y, (double)t);



	return 0;
}
