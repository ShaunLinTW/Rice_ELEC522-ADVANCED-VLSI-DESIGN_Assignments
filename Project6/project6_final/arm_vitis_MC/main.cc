#include <iostream>
#include <stdio.h>
#include "xil_printf.h"
#include <unistd.h>
#include "xtime_l.h"
#include "xparameters.h"
#include "xtime_l.h"
#include "xscugic.h"
#include "ap_fixed.h"
#include "linearsolver_system.h"

linearsolver_system Linearsolver_system;

using namespace std;

typedef ap_fixed<16, 3, AP_RND, AP_SAT> THETA_TYPE;

int get_int_reinterpret(THETA_TYPE x) {
	return *(reinterpret_cast<short*>(&x));
}

THETA_TYPE get_fixed_reinterpret(int x) {
	return *(reinterpret_cast<THETA_TYPE*>(&x));
}

int main()
{
	cout << "--- Start of the Program ---" << endl;

	// set control signal
	bool rst;
	rst = false;

	// inputs A1 Matrix
	THETA_TYPE A_col1[4] = {0.6900, 0.5054, 0.5914, 0.5547};
	THETA_TYPE A_col2[4] = {0.3784, 0.2577, 0.2073, 0.6262};
	THETA_TYPE A_col3[4] = {0.3401, 0.8438, 0.0687, 0.4099};
	THETA_TYPE A_col4[4] = {0.8799, 0.3194, 0.9805, 0.0850};

	signed int uA_col1_In = get_int_reinterpret(A_col1);
	signed int uA_col2_In = get_int_reinterpret(A_col2);
	signed int uA_col3_In = get_int_reinterpret(A_col3);
	signed int uA_col4_In = get_int_reinterpret(A_col4);

	linearsolver_system_Initialize(&Linearsolver_system, 0);
	linearsolver_system_A_col1_write(&Linearsolver_system, uA_col1_In);
	linearsolver_system_A_col2_write(&Linearsolver_system, uA_col2_In);
	linearsolver_system_A_col3_write(&Linearsolver_system, uA_col3_In);
	linearsolver_system_A_col4_write(&Linearsolver_system, uA_col4_In);

	// print A1 Matrix in ARM core
	cout << "A1 = " << endl;
	for (int i = 0; i < 4; i++) {
		cout << " " << uA_col1_In[i] << " ";
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		cout << " " << uA_col2_In[i] << " ";
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		cout << " " << uA_col3_In[i] << " ";
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		cout << " " << uA_col4_In[i] << " ";
		cout << endl;
	}

	// inputs b1 Vector
	THETA_TYPE b[4] = {0.4, 0.2, 0.9, 0.5};

	signed int ub_In = get_int_reinterpret(b);

	linearsolver_system_Initialize(&Linearsolver_system, 0);
	linearsolver_system_b_In_write(&Linearsolver_system, ub_In);

	linearsolver_system_rst_write(&Linearsolver_system, true);
	linearsolver_system_rst_write(&Linearsolver_system, false);

	// print b1 Vector in ARM core
	cout << "b1 = " << endl;
	for (int i = 0; i < 4; i++) {
		cout << " " << ub_In[i] << " ";
		cout << endl;
	}

	linearsolver_system_rst_write(&Linearsolver_system, true);

	// output x1 Vector
	THETA_TYPE x[4] = {0};

	signed int ux_out;

	ux_out = linearsolver_system_block_x_col_out_read(&Linearsolver_system);
	x = get_fixed_reinterpret(ux_out);

	linearsolver_system_rst_write(&Linearsolver_system, true);
	linearsolver_system_rst_write(&Linearsolver_system, false);

	// print x1 Vector results in ARM core
	cout << "Result vector x1 using ARM core:" << endl;
	for (int i = 0; i < 4; i++) {
		cout << " " << x[i] << " ";
		cout << endl;
	}

	//-------------------------------------------------------------------------------------------------
	
	// inputs A2 Matrix
	THETA_TYPE A_col1[4] = {0.1, 0.1, 0.4, 0.3};
	THETA_TYPE A_col2[4] = {0.2, 0.8, 0.6, 0.5};
	THETA_TYPE A_col3[4] = {0.9, 0.1, 0.3, 0.2};
	THETA_TYPE A_col4[4] = {0.3, 0.1, 0.4, 0.6};

	signed int uA_col1_In = get_int_reinterpret(A_col1);
	signed int uA_col2_In = get_int_reinterpret(A_col2);
	signed int uA_col3_In = get_int_reinterpret(A_col3);
	signed int uA_col4_In = get_int_reinterpret(A_col4);

	linearsolver_system_Initialize(&Linearsolver_system, 0);
	linearsolver_system_A_col1_write(&Linearsolver_system, uA_col1_In);
	linearsolver_system_A_col2_write(&Linearsolver_system, uA_col2_In);
	linearsolver_system_A_col3_write(&Linearsolver_system, uA_col3_In);
	linearsolver_system_A_col4_write(&Linearsolver_system, uA_col4_In);

	// print A2 Matrix in ARM core
	cout << "A2= " << endl;
	for (int i = 0; i < 4; i++) {
		cout << " " << uA_col1_In[i] << " ";
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		cout << " " << uA_col2_In[i] << " ";
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		cout << " " << uA_col3_In[i] << " ";
		cout << endl;
	}
	for (int i = 0; i < 4; i++) {
		cout << " " << uA_col4_In[i] << " ";
		cout << endl;
	}

	// inputs b2 Vector
	THETA_TYPE b[4] = {0.2, 0.1, 0.8, 0.4};

	signed int ub_In = get_int_reinterpret(b);

	linearsolver_system_Initialize(&Linearsolver_system, 0);
	linearsolver_system_b_In_write(&Linearsolver_system, ub_In);

	linearsolver_system_rst_write(&Linearsolver_system, true);
	linearsolver_system_rst_write(&Linearsolver_system, false);

	// print b2 Vector in ARM core
	cout << "b2 = " << endl;
	for (int i = 0; i < 4; i++) {
		cout << " " << ub_In[i] << " ";
		cout << endl;
	}

	// output x2 Vector
	THETA_TYPE x[4] = {0};

	signed int ux_out;

	ux_out = linearsolver_system_block_x_col_out_read(&Linearsolver_system);
	x = get_fixed_reinterpret(ux_out);

	linearsolver_system_rst_write(&Linearsolver_system, true);
	linearsolver_system_rst_write(&Linearsolver_system, false);

	// print x2 Vector results in ARM core
	cout << "Result vector x2 using ARM core:" << endl;
	for (int i = 0; i < 4; i++) {
		cout << " " << x[i] << " ";
		cout << endl;
	}

	cout << "--- End of the Program ---" << endl;

	return 0;
}