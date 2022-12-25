#include <math.h>
#include "linearsolver.h"

using namespace std;

// Matrix A
THETA_TYPE A[4][4] = {0};
THETA_TYPE A1[4][4] = {{0.1, 0.1, 0.4, 0.3},
                   	   {0.2, 0.8, 0.6, 0.5},
					   {0.9, 0.1, 0.3, 0.2},
					   {0.3, 0.1, 0.4, 0.6}};
THETA_TYPE A2[4][4] = {{0.6900, 0.5054, 0.5914, 0.5547},
      	  	 	   	   {0.3784, 0.2577, 0.2073, 0.6262},
					   {0.3401, 0.8438, 0.0687, 0.4099},
					   {0.8799, 0.3194, 0.9805, 0.0850}};

// Vector b
THETA_TYPE b[4] = {0};
THETA_TYPE b1[4] = {0.2, 0.1, 0.8, 0.4};
THETA_TYPE b2[4] = {0.4, 0.2, 0.9, 0.5};
THETA_TYPE b_verify[4] = {0};

//Vector x
THETA_TYPE x[4] = {0};

//Matrix QT, R
THETA_TYPE QT[4][4] = {0};
THETA_TYPE R[4][4] = {0};

int main(int argc, char **argv)
{
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			A[i][j] = A1[i][j]; // change your A Matrix here
		}
	}
	for (int i = 0; i < 4; i++) {
		b[i] = b1[i]; // change your b vector here
	}

	cout << "--- Start of Testbench ---" << endl;

//	print A Matrix
	cout << "A = " << endl;
	  for (int i = 0; i < 4; i++) {
	    for (int j = 0; j < 4; j++) {
	      cout << " " << A[i][j] << " ";
	    }
	    cout << endl;
	  }
	  cout << endl;

//	  print b Vector
	  cout << "b = " << endl;
	  for (int i = 0; i < 4; i++) {
		  cout << " " << b[i] << " ";
		  cout << endl;
	  }
	  cout << endl;
//------------------LinearSolver() function----------------------------------
//	  call LinearSolver() function, Ax = b
	  LinearSolver(A, b, x);
//	  print x Vector results
	  cout << "Result vector x:" << endl;
	  for (int i = 0; i < 4; ++i) {
		  cout << " " << x[i] << endl;
	  }
	  cout << endl;
//	  verify A*x = b
	  for (int i = 0; i < 4; ++i) {
		  for (int j = 0; j < 4; ++j) {
			  b_verify[i] += A[i][j] * x[j];
	  	  }
	  }
	  cout << endl;
	  cout << "Solve Ax = b using above x vector to verify vector b:" << endl;
	  for (int i = 0; i < 4; ++i) {
		  cout << " " << b_verify[i] << endl;
	  }
	  cout << endl;
//------------------qr_decomposition() function to verify--------------------
//	  call qr_sw() function to calculate QT, R
	  qr_decomposition(A, QT, R);
	  cout << "Verify QT = " << endl;
	  for (int i = 0; i < 4; i++) {
		  for (int j = 0; j < 4; j++) {
			  cout << " " << QT[i][j] << " ";
		  }
		  cout << endl;
	  }
	  cout << "Verify R = " << endl;
	  for (int i = 0; i < 4; i++) {
		  for (int j = 0; j < 4; j++) {
			  cout << " " << R[i][j] << " ";
		  }
		  cout << endl;
	  }
	  cout << endl;

	cout << "--- End of Testbench ---" << endl;

	return 0;
}
