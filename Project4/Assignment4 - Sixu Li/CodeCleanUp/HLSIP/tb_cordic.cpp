
#include "cordic.h"

#define PI 3.1415926

int main(){
	
	FIXDT t = (FIXDT) (30.0 * PI / 180);
	FIXDT ts = 0.886025;
	FIXDT tc = 0.5;
	
	FIXDT CS_O_COS, CS_O_SIN, IA_O_IAT;
	FIXDT sin_out, cos_out, theta;
	
	short done;


	cordic(0, t, ts, tc, CS_O_SIN, CS_O_COS, IA_O_IAT, done);
	printf("result sin = %f, cos = %f\n, theta = %f\n", (float)CS_O_SIN, (float)CS_O_COS, (float)IA_O_IAT );

	cordic(1, t, ts, tc, CS_O_SIN, CS_O_COS, IA_O_IAT, done);
	printf("result sin = %f, cos = %f\n, theta = %f\n", (float)CS_O_SIN, (float)CS_O_COS, (float)IA_O_IAT/ PI * 180.0 );

	return 0;
}
