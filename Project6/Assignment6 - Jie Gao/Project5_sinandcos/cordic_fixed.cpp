// The file cordic.h holds definitions for the data types and constant values
#include "cordic.h"

// The cordic_phase array holds the angle for the current rotation
// cordic_phase[0] =~ 0.785
// cordic_phase[1] =~ 0.463
//

void sin_cos(THETA_TYPE theta,COS_SIN_TYPE x,COS_SIN_TYPE y,COS_SIN_TYPE &s, COS_SIN_TYPE &c)
{

	  COS_SIN_TYPE current_cos = x;
	  COS_SIN_TYPE temp_cos ;
	  temp_cos = current_cos - (current_cos >> 1);
	  current_cos = temp_cos;
	  temp_cos = current_cos + (current_cos >> 2);
	  current_cos = temp_cos;
	  temp_cos = current_cos - (current_cos >> 5);
	  current_cos = temp_cos;
	  temp_cos = current_cos + (current_cos >> 9);
	  current_cos = temp_cos;
	  temp_cos = current_cos + (current_cos >> 10);
	  current_cos = temp_cos;
	  temp_cos = current_cos + (current_cos >> 12);
	  current_cos = temp_cos;
	  COS_SIN_TYPE current_sin = y;
	  COS_SIN_TYPE temp_sin ;
	  temp_sin = current_sin - (current_sin >> 1);
	  current_sin = temp_sin;
	  temp_sin = current_sin + (current_sin >> 2);
	  current_sin = temp_sin;
	  temp_sin = current_sin - (current_sin >> 5);
	  current_sin = temp_sin;
	  temp_sin = current_sin + (current_sin >> 9);
	  current_sin = temp_sin;
	  temp_sin = current_sin + (current_sin >> 10);
	  current_sin = temp_sin;
	  temp_sin = current_sin + (current_sin >> 12);
	  current_sin = temp_sin;
	  THETA_TYPE half_Pi = 1.5707;
	  THETA_TYPE zero = 0;

	  int i;
	  i = 0;

	  for(int k=0; k <= 4;k++)
	      if(theta > half_Pi){
	    	  theta = theta - half_Pi;
	    	  i++;
	      }

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

	    if( i == 1){
	  	  current_cos = 0-current_cos;
	    }
	    if( i == 2){
	   	  current_sin = 0-current_sin;
	   	  current_cos = 0-current_cos;
	     }
	    if( i == 3){
	   	  current_sin = 0-current_sin;
	     }

	    // Set the final sine and cosine values

	    s = current_sin;  c = current_cos;
}
