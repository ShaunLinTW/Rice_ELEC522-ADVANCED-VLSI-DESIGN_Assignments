#include <iostream>
#include <cmath>
#include "ap_fixed.h"
#include "xparameters.h"
#include "xtime_l.h"
#include "xscugic.h"
#include "linearsystemsolver.h"
#include "linearsolver.h"

Linearsolver linearsolver;

using namespace std;

typedef ap_fixed<16,3> THETA_TYPE;

unsigned int get_int_reinterpret(THETA_TYPE x) {
	return *(reinterpret_cast<unsigned int *>(&x));
}

THETA_TYPE get_fixed_reinterpret(unsigned int x) {
	return *(reinterpret_cast<THETA_TYPE *>(&x));
}

// actual MAIN control program running on ARM processor PS
int main()
{
	cout << "--- Start of the Program ---" << endl;

	THETA_TYPE A1[4][4] = {{0.1, 0.1, 0.4, 0.3},
						   {0.2, 0.8, 0.6, 0.5},
						   {0.9, 0.1, 0.3, 0.2},
						   {0.3, 0.1, 0.4, 0.6}};
	
	cout << "A1 = " << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << " " << A1[i][j] << " ";
		}
		cout << endl;
	}

	THETA_TYPE b1[4] = {0.2, 0.1, 0.8, 0.4};

	cout << "b1 = " << endl;
	for (int i = 0; i < 4; i++) {
		cout << " " << b1[i] << " ";
		cout << endl;
	}

	THETA_TYPE x1[4] = {0};

	unsigned int ua1 = get_int_reinterpret(A1);
	unsigned int ub1 = get_int_reinterpret(b1);

    unsigned int ux1[4];

	Linearsolver_Initialize(&linearsolver, 0);

	Linearsolver_Set_A(&linearsolver, ua1);
	Linearsolver_Set_b(&linearsolver, ub1);

	Linearsolver_Start(&linearsolver);

	ux1 = Linearsolver_Get_x(&linearsolver);
	x1 = get_fixed_reinterpret(ux1);

	cout << "Result vector x1 using ARM core:" << endl;
	for (int i = 0; i < 4; ++i) {
		cout << " " << x1[i] << endl;
	}
	
	THETA_TYPE A2[4][4] = {{0.6900, 0.5054, 0.5914, 0.5547},
						   {0.3784, 0.2577, 0.2073, 0.6262},
						   {0.3401, 0.8438, 0.0687, 0.4099},
						   {0.8799, 0.3194, 0.9805, 0.0850}};

	cout << "A2 = " << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			cout << " " << A2[i][j] << " ";
		}
		cout << endl;
	}

	THETA_TYPE b2[4] = {0.4, 0.2, 0.9, 0.5};

	cout << "b2 = " << endl;
	for (int i = 0; i < 4; i++) {
		cout << " " << b2[i] << " ";
		cout << endl;
	}
	
	THETA_TYPE x2[4] = {0};
	
	unsigned int ua2 = get_int_reinterpret(A2);
	unsigned int ub2 = get_int_reinterpret(b2);
	
	unsigned int ux2[4];

	Linearsolver_Initialize(&linearsolver, 0);

	Linearsolver_Set_A(&linearsolver, ua2);
	Linearsolver_Set_b(&linearsolver, ub2);

	Linearsolver_Start(&linearsolver);

	ux2 = Linearsolver_Get_x(&linearsolver);
	x2 = get_fixed_reinterpret(ux2);

	cout << "Result vector x2 using ARM core:" << endl;
	for (int i = 0; i < 4; ++i) {
		cout << " " << x2[i] << endl;
	}

    cout << "--- End of the Program ---" << endl;


	return 0;
}