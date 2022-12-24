#import "cordic.h"

int main(){
	CORDIC_MAG_TYPE sine;
	CORDIC_MAG_TYPE cosine;
	
	CORDIC_ANG_TYPE desired_angle;
	
	circular_cordic(desired_angle, &cosine, &sine);
	
	return 0;
}
