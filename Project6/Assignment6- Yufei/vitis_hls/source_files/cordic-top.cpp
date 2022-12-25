#include <math.h>
#include"cordic.h"
#include <stdio.h>
#include <stdlib.h>

using namespace std;

int main(int argc, char **argv)
{	
	THETA_TYPE radian; 		//radian versuin of degree

	//vector input
	VECTOR_TYPE x_in = 1;
	VECTOR_TYPE y_in = 0;
	VECTOR_TYPE x_out;
	VECTOR_TYPE y_out;

	//initialize the mode to cosine&sine mode
	bool mode = 0;

	//error checking
	double expected_val1;
	double expected_val2;
	double vector_sum = 0;
	double vector_error_sum = 0;
	double degree_sum = 0;
	double degree_error_sum = 0;

	//perform the cosine&sine mode
	printf("******************************************************************************************************************\n");
	printf("perform the cosine&sine mode\n");
	printf("******************************************************************************************************************\n");
	for(int i=0;i<NUM_DEGREE;i++) {
			radian = i*M_PI/180;
			cordic(radian, x_in, y_in, x_out, y_out, mode);
			expected_val1 = (double)x_in*cos((double)radian)-(double)y_in*sin((double)radian);
			expected_val2 = (double)y_in*cos((double)radian)+(double)x_in*sin((double)radian);
			vector_error_sum += fabs(expected_val1) + fabs(expected_val2) - fabs((double)x_out) - fabs((double)y_out);
			vector_sum += fabs(expected_val1) + fabs(expected_val2);
			printf("input:[degree=%2.1f\tradian=%f\tinput_x=%f\tinput_y=%f]\toutput:[XcosT-YsinT=%f\tYcosT+XsinT=%f]\n",
					(double)i, (double)radian, (double)x_in, (double)y_in, (double)x_out, (double)y_out);
	}
	//calculate and print the error
	printf("vector length error = %f%\n",vector_error_sum/vector_sum*100);

	//change the mode to arctan&radius mode
	mode = 1;

	//perform the  arctan&radius mode
	printf("******************************************************************************************************************\n");
	printf("perform the  arctan&radius mode\n");
	printf("******************************************************************************************************************\n");
	for(int i=0;i<NUM_DEGREE;i++) {
		radian = i*M_PI/180;
		y_in = sin((double)radian);
		x_in = cos((double)radian);
		cordic(0, x_in, y_in, x_out, y_out, mode);
		expected_val1 = sqrt(pow((double)x_in,2)+pow((double)y_in,2));
		expected_val2 = radian;
		vector_error_sum += fabs((double)x_out-expected_val1);
		vector_sum += expected_val1;
		degree_error_sum += fabs((double)y_out-expected_val2);
		degree_sum += expected_val2;
		printf("input:[degree=%2.1f\tradian=%f\tinput_x=%f\tinput_y=%f]\toutput:[raduis=%f\ttheta=%f]\n",
				(float)i, (double)radian, (double)x_in, (double)y_in, (double)x_out, (double)y_out);
	}
	//calculate and print the error
	printf("vector length error = %f%\n",vector_error_sum/vector_sum*100);
	printf("degree error = %f%\n",degree_error_sum/degree_sum*100);

//	VECTOR_TYPE terget = 0.6072529350088812561694;
//	VECTOR_TYPE current_num = 0;
//	VECTOR_TYPE current_num1 = 0;
//	VECTOR_TYPE num = 1;
//	VECTOR_TYPE x = 2;
//
//	for(int i = 0; i<32; i++)
//	{
//		if(terget>=current_num)
//		{
//			current_num+=num;
//			current_num1+=x;
//			printf("+\n");
//		}
//		else
//		{
//			current_num-=num;
//			current_num1-=x;
//			printf("-\n");
//		}
//		num = num>>1;
//		x = x>>1;
//	}
//	printf("\nnum=%f,x=%f",(double)current_num,double(current_num1));

	return 0;
}
