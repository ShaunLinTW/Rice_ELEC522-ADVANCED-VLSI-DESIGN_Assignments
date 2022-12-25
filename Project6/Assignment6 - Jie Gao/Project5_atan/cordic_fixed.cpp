// The file cordic.h holds definitions for the data types and constant values
#include "cordic.h"

// The cordic_phase array holds the angle for the current rotation
// cordic_phase[0] =~ 0.785
// cordic_phase[1] =~ 0.463
//

void atan(COS_SIN_TYPE x,COS_SIN_TYPE y,THETA_TYPE &atan,THETA_TYPE &R)
{

  // Set the initial vector that we will rotate
  // current_cos = I; current_sin = Q

  THETA_TYPE half_Pi = 1.5707;
  THETA_TYPE zero = 0;


  THETA_TYPE z = 0;
  COS_SIN_TYPE tan = 1;
  THETA_TYPE x_v,y_v;
  int d = 0;
  int e = 0;

  // This loop iteratively rotates the initial vector to find the
  // sine and cosine values corresponding to the input theta angle

	  if(x < 0 && y <= 0 ){
		  e = 2;
		  x = 0 - x;
		  y = 0 - y;
	  }
	  else if(x <= 0 && y > 0)
	  {
		  x = 0 - x;
		  e = 1;
	  }
	  else if(x >= 0 && y < 0)
	 	  {
	 		  y = 0 - y;
	 		  e = 3;
	 	  }
	  else if(x == 0 && y == 0 )
	  {
		  	e = 4;
	  }
	  else{
		  e = 0;
	  }


	  for (int k = 0; k < NUM_ITERATIONS; k++) {

		  x_v = x>>k;
		  y_v = y>>k;

	  	 if(y >= 0){
	  		x = x + y_v;
	  		y = y - x_v;
		 z = z + cordic_phase[k];

	  	 	  			}

	  	 	 else{
	  	 	  x = x - y_v;
	  	 	  y = y + x_v;
	  	 	  z = z - cordic_phase[k];
	  	 		}


	     }


  if( e == 0){
  	   z = z;
     }
     else if( e == 1){
     	   z = half_Pi + half_Pi - z;
        }
     else if( e == 2){
       	   z = half_Pi + half_Pi + z;
          }
     else if( e == 3){
       	   z = half_Pi + half_Pi + half_Pi +half_Pi - z ;
          }
     else if (e == 4){
    	   z = 0;
     }




  R = x - (x >> 1);
  x = R;
  R = x + (x >> 2);
  x = R;
  R = x - (x >> 5);
  x = R;
  R = x + (x >> 9);
  x = R;
  R = x + (x >> 10);
  x = R;
  R = x + (x >> 12);
  R = x;

  atan = z;

}


