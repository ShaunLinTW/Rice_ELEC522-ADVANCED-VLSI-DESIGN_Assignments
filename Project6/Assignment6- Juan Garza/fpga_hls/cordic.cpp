// The file cordic.h holds definitions for the data types and constant values
#include "cordic.h"

// The cordic_phase array holds the angle for the current rotation
// cordic_phase[0] =~ 0.785
// cordic_phase[1] =~ 0.463

void cordic(bool state, THETA_TYPE theta, COS_SIN_TYPE x, COS_SIN_TYPE y, COS_SIN_TYPE &s, COS_SIN_TYPE &c, THETA_TYPE_in &t)
{


  // Set the initial vector that we will rotate
  // current_cos = I; current_sin = Q
  COS_SIN_TYPE current_cos = x;
  COS_SIN_TYPE current_sin = y;


  THETA_TYPE_in current_t =0;
  COS_SIN_TYPE y_compare =0;
  COS_SIN_TYPE x_s =0;
  COS_SIN_TYPE y_s =0;
//  COS_SIN_TYPE factor = 1.0;
 // THETA_TYPE current_theta = 0;
  const int NUM_ITERATIONS=32;

  // This loop iteratively rotates the initial vector to find the
  // sine and cosine values corresponding to the input theta angle
  double theta_i = theta;
  int i = 1;

#pragma HLS PIPELINE II=1

  //cos and sin
  if (state){

	   if ((x == 0) and (y==0)){current_t = 0;y_s =0;x_s =0;}else{

  for (int j = 0; j < NUM_ITERATIONS; j++) {
      // Multiply previous iteration by 2^(-j).  This is equivalent to
      // a right shift by j on a fixed-point number.
      COS_SIN_TYPE cos_shift = current_cos >> j;
      COS_SIN_TYPE sin_shift = current_sin >> j;
    // Determine if we are rotating by a positive or negative angle
    if(theta >= 0) {
        // Perform the rotation
        current_cos = current_cos - sin_shift;
        current_sin = current_sin + cos_shift;
        // Determine the new theta
        theta = theta - cordic_phase[j];
    } else {
        // Perform the rotation
        current_cos = current_cos + sin_shift;
        current_sin = current_sin - cos_shift;
        // Determine the new theta
        theta = theta + cordic_phase[j];
		}
	  }
    x_s = current_cos;
    y_s = current_sin;
  //constant Shift
	 x_s = x_s - (x_s >> 1);
	 x_s = x_s + (x_s >> 2);
	 x_s = x_s - (x_s >> 5);
	 x_s = x_s + (x_s >> 10);
	 x_s = x_s + (x_s >> 16);
	 x_s = x_s + (x_s >> 19);
	 x_s = x_s + (x_s >> 22);
	 y_s = y_s - (y_s >> 1);
	 y_s = y_s + (y_s >> 2);
	 y_s = y_s - (y_s >> 5);
	 y_s = y_s + (y_s >> 10);
	 y_s = y_s + (y_s >> 16);
	 y_s = y_s + (y_s >> 19);
	 y_s = y_s + (y_s >> 22);


  }}

  //Arctan fucntion
  if (!state){
	   if ((x == 0) and (y==0)){
		   current_t = 0;
		   y_s =0;
		   x_s =0;
	   }
	   else{
  y_compare = y;

  for (int j = 0; j < NUM_ITERATIONS; j++) {
      COS_SIN_TYPE cos_shift = current_cos >> j;
      COS_SIN_TYPE sin_shift = current_sin >> j;

    if(y_compare >= 0) {
        // Perform the rotation
        current_cos = current_cos + sin_shift;
        current_sin = current_sin - cos_shift;
        // Determine the new theta
        current_t = current_t + cordic_phase[j];
        y_compare = current_sin;
    } else {
        // Perform the rotation
        current_cos = current_cos - sin_shift;
        current_sin = current_sin + cos_shift;
        // Determine the new theta
        y_compare = current_sin;
        current_t = current_t - cordic_phase[j];
		}
	  }

  x_s = current_cos;
  y_s = current_sin;
//constant Shift
	 x_s = x_s - (x_s >> 1);
	 x_s = x_s + (x_s >> 2);
	 x_s = x_s - (x_s >> 5);
	 x_s = x_s + (x_s >> 10);
	 x_s = x_s + (x_s >> 16);
	 x_s = x_s + (x_s >> 19);
	 x_s = x_s + (x_s >> 22);
	 y_s = y_s - (y_s >> 1);
	 y_s = y_s + (y_s >> 2);
	 y_s = y_s - (y_s >> 5);
	 y_s = y_s + (y_s >> 10);
	 y_s = y_s + (y_s >> 16);
	 y_s = y_s + (y_s >> 19);
	 y_s = y_s + (y_s >> 22);


  }}

  t = current_t;
  s = y_s;  c = x_s;
}



/*
	 if (i ==1){
	current_cos = x_s;
	current_sin = y_s;
	 }
	 if (i ==2){
	current_cos = -x_s;
	current_sin = y_s;
	 }
	 if (i ==3){
	current_cos = -x_s;
	current_sin = -y_s;
	 }
	 if (i ==4){
	current_cos = x_s;
	current_sin = -y_s;
	 }

    current_cos = x_s;
    current_sin = y_s;
    ///  while (theta_i > 0){
	//  if (i >4){
		//  i = 1;
	 // }
//	  theta_i = theta_i - 1.5707;
  //}


    */
