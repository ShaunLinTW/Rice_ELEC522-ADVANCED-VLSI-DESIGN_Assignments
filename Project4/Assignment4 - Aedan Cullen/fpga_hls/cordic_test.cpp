#include "cordic.h"

int main(int argc, char **argv) {

	FIXED final_x;
	FIXED final_y;
	bool mode = false;
	FIXED mode0_theta = 3.1415926/4;
	FIXED mode1_theta;

	cordic(1, 0, &final_x, &final_y, mode, mode0_theta, &mode1_theta);

	cout << endl;
	cout << final_x << endl;
	cout << final_y << endl;
	cout << mode1_theta << endl;

}

