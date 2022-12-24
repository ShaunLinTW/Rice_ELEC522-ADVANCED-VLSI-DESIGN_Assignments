#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring> // for memset
#include <limits>

#include <stdio.h>
#include "xil_printf.h"
#include <unistd.h>
#include "xtime_l.h"
#include "xparameters.h"
#include "xtime_l.h"
#include "xscugic.h"
#include "ap_fixed.h"
#include "qrd_system.h"

qrd_system QRD_system;

using namespace std;

typedef ap_fixed<16, 3, AP_RND, AP_SAT> THETA_TYPE;

int get_int_reinterpret(THETA_TYPE x) {
	return *(reinterpret_cast<short*>(&x));
}

THETA_TYPE get_fixed_reinterpret(int x) {
	return *(reinterpret_cast<THETA_TYPE*>(&x));
}


class Vector;

class Matrix {

public:
  // default constructor (don't allocate)
  Matrix() : m(0), n(0), data(nullptr) {}

  // constructor with memory allocation, initialized to zero
  Matrix(int m_, int n_) : Matrix() {
    m = m_;
    n = n_;
    allocate(m_,n_);
  }

  // copy constructor
  Matrix(const Matrix& mat) : Matrix(mat.m,mat.n) {

    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
	(*this)(i,j) = mat(i,j);
  }

  // constructor from array
  template<int rows, int cols>
  Matrix(double (&a)[rows][cols]) : Matrix(rows,cols) {

    for (int i = 0; i < m; i++)
      for (int j = 0; j < n; j++)
	(*this)(i,j) = a[i][j];
  }

  // destructor
  ~Matrix() {
    deallocate();
  }


  // access data operators
  double& operator() (int i, int j) {
    return data[i+m*j]; }
  double  operator() (int i, int j) const {
    return data[i+m*j]; }

  // operator assignment
  Matrix& operator=(const Matrix& source) {

    // self-assignment check
    if (this != &source) {
      if ( (m*n) != (source.m * source.n) ) { // storage cannot be reused
	allocate(source.m,source.n);          // re-allocate storage
      }
      // storage can be used, copy data
      std::copy(source.data, source.data + source.m*source.n, data);
    }
    return *this;
  }

  // compute minor
  void compute_minor(const Matrix& mat, int d) {

    allocate(mat.m, mat.n);

    for (int i = 0; i < d; i++)
      (*this)(i,i) = 1.0;
    for (int i = d; i < mat.m; i++)
      for (int j = d; j < mat.n; j++)
	(*this)(i,j) = mat(i,j);

  }

  // Matrix multiplication
  // c = a * b
  // c will be re-allocated here
  void mult(const Matrix& a, const Matrix& b) {

    if (a.n != b.m) {
      std::cerr << "Matrix multiplication not possible, sizes don't match !\n";
      return;
    }

    // reallocate ourself if necessary i.e. current Matrix has not valid sizes
    if (a.m != m or b.n != n)
      allocate(a.m, b.n);

    memset(data,0,m*n*sizeof(double));

    for (int i = 0; i < a.m; i++)
      for (int j = 0; j < b.n; j++)
	for (int k = 0; k < a.n; k++)
	  (*this)(i,j) += a(i,k) * b(k,j);

  }

  void transpose() {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < i; j++) {
	double t = (*this)(i,j);
	(*this)(i,j) = (*this)(j,i);
	(*this)(j,i) = t;
      }
    }
  }

  // take c-th column of m, put in v
  void extract_column(Vector& v, int c);

  // memory allocation
  void allocate(int m_, int n_) {

    // if already allocated, memory is freed
    deallocate();

    // new sizes
    m = m_;
    n = n_;

    data = new double[m_*n_];
    memset(data,0,m_*n_*sizeof(double));

  } // allocate

  // memory free
  void deallocate() {

    if (data)
      delete[] data;

    data = nullptr;

  }

  int m, n;

private:
  double* data;

}; // struct Matrix

// column vector
class Vector {

public:
  // default constructor (don't allocate)
  Vector() : size(0), data(nullptr) {}

  // constructor with memory allocation, initialized to zero
  Vector(int size_) : Vector() {
    size = size_;
    allocate(size_);
  }

  // destructor
  ~Vector() {
    deallocate();
  }

  // access data operators
  double& operator() (int i) {
    return data[i]; }
  double  operator() (int i) const {
    return data[i]; }

  // operator assignment
  Vector& operator=(const Vector& source) {

    // self-assignment check
    if (this != &source) {
      if ( size != (source.size) ) {   // storage cannot be reused
	allocate(source.size);         // re-allocate storage
      }
      // storage can be used, copy data
      std::copy(source.data, source.data + source.size, data);
    }
    return *this;
  }

  // memory allocation
  void allocate(int size_) {

    deallocate();

    // new sizes
    size = size_;

    data = new double[size_];
    memset(data,0,size_*sizeof(double));

  } // allocate

  // memory free
  void deallocate() {

    if (data)
      delete[] data;

    data = nullptr;

  }

  //   ||x||
  double norm() {
    double sum = 0;
    for (int i = 0; i < size; i++) sum += (*this)(i) * (*this)(i);
    return sqrt(sum);
  }

  // divide data by factor
  void rescale(double factor) {
    for (int i = 0; i < size; i++) (*this)(i) /= factor;
  }

  void rescale_unit() {
    double factor = norm();
    rescale(factor);
  }

  int size;

private:
  double* data;

}; // class Vector

// c = a + b * s
void vmadd(const Vector& a, const Vector& b, double s, Vector& c)
{
  if (c.size != a.size or c.size != b.size) {
    std::cerr << "[vmadd]: vector sizes don't match\n";
    return;
  }

  for (int i = 0; i < c.size; i++)
    c(i) = a(i) + s * b(i);
}

// mat = I - 2*v*v^T
// !!! m is allocated here !!!
void compute_householder_factor(Matrix& mat, const Vector& v)
{

  int n = v.size;
  mat.allocate(n,n);
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      mat(i,j) = -2 *  v(i) * v(j);
  for (int i = 0; i < n; i++)
    mat(i,i) += 1;
}

// take c-th column of a matrix, put results in Vector v
void Matrix::extract_column(Vector& v, int c) {
  if (m != v.size) {
    std::cerr << "[Matrix::extract_column]: Matrix and Vector sizes don't match\n";
    return;
  }

  for (int i = 0; i < m; i++)
    v(i) = (*this)(i,c);
}

void matrix_show(const Matrix&  m, const std::string& str="")
{
  std::cout << str << "\n";
  for(int i = 0; i < m.m; i++) {
    for (int j = 0; j < m.n; j++) {
      printf(" %8.4f", m(i,j));
    }
    printf("\n");
  }
  printf("\n");
}

// L2-norm ||A-B||^2
double matrix_compare(const Matrix& A, const Matrix& B) {
  // matrices must have same size
  if (A.m != B.m or  A.n != B.n)
    return std::numeric_limits<double>::max();

  double res=0;
  for(int i = 0; i < A.m; i++) {
    for (int j = 0; j < A.n; j++) {
      res += (A(i,j)-B(i,j)) * (A(i,j)-B(i,j));
    }
  }

  res /= A.m*A.n;
  return res;
}

void householder(Matrix& mat, Matrix& R, Matrix& Q)
{

  int m = mat.m;
  int n = mat.n;

  // array of factor Q1, Q2, ... Qm
  std::vector<Matrix> qv(m);

  // temp array
  Matrix z(mat);
  Matrix z1;

  for (int k = 0; k < n && k < m - 1; k++) {

    Vector e(m), x(m);
    double a;

    // compute minor
    z1.compute_minor(z, k);

    // extract k-th column into x
    z1.extract_column(x, k);

    a = x.norm();
    if (mat(k,k) > 0) a = -a;

    for (int i = 0; i < e.size; i++)
      e(i) = (i == k) ? 1 : 0;

    // e = x + a*e
    vmadd(x, e, a, e);

    // e = e / ||e||
    e.rescale_unit();

    // qv[k] = I - 2 *e*e^T
    compute_householder_factor(qv[k], e);

    // z = qv[k] * z1
    z.mult(qv[k], z1);

  }

  Q = qv[0];

  // after this loop, we will obtain Q (up to a transpose operation)
  for (int i = 1; i < n && i < m - 1; i++) {

    z1.mult(qv[i], Q);
    Q = z1;

  }

  R.mult(Q, mat);
  Q.transpose();
}

double A1_input[][4] = {
  { 0.6900, 0.5054, 0.5914, 0.5547},
  { 0.3784, 0.2577, 0.2073, 0.6262},
  { 0.3401, 0.8438, 0.0687, 0.4099},
  { 0.8799, 0.3194, 0.9805, 0.0850},
};

double A2_input[][4] = {
  { 0.3564, 0.7160, 0.9118, 0.0091},
  { 0.8255, 0.3252, 0.0785, 0.0412},
  { 0.6638, 0.5491, 0.9037, 0.3417},
  { 0.7119, 0.4366, 0.7662, 0.6734},
};

//double Q1_input[][4] = {
//  { -0.5612, 0.0613, -0.1067, 0.8098},
//  { -0.3063, 0.0037, -0.8832, -0.3312},
//  { -0.2737, 0.9028, 0.1866, -0.2367},
//  { -0.7069, -0.4047, 0.3910, -0.4070},
//};

//double R1_input[][4] = {
//  { 1.2269, -0.8223, -1.1075, -0.6766},
//  { 0.0000, 0.6697, 0.2980, -0.3732},
//  { 0.0000, 0.0000, 0.1533, 0.5021},
//  { 0.0000, 0.0000, 0.0000, 0.1139},
//};

//double Q2_input[][4] = {
//  { -0.2695, 0.8696, -0.3505, 0.1942},
//  { -0.6202, -0.4427, -0.6370, -0.0403},
//  { -0.4967, 0.1744, 0.4104, -0.7333},
//  { -0.5286, -0.0919, 0.5365, 0.6351},
//};

//double R2_input[][4] = {
//  { 1.3193, -0.8992, -1.1514, -0.5531},
//  { 0.0000, 0.5378, -0.8481, 0.0131},
//  { 0.0000, 0.0000, 0.4120, -0.4711},
//  { 0.0000, 0.0000, 0.0000, 0.1779},
//};

int main()
{
	cout << "--- Start of the Program ---" << endl;
    Matrix A1(A1_input);
    Matrix Q1, R1;

    cout << "--- Input A Matrix: ---" << endl;
    matrix_show(A1,"A1:");

    // compute QR decompostion
    householder(A1, R1, Q1);

    cout << "--- QRD results calculated from Arm core ---" << endl;

    matrix_show(Q1,"Q1:");
    matrix_show(R1,"R1:");

    // compare Q*R to the original matrix A
//    Matrix A_check;
//    A_check.mult(Q, R);

    Matrix A2(A2_input);
    Matrix Q2, R2;

    cout << "--- Input A Matrix: ---" << endl;

    matrix_show(A2,"A2:");

    // compute QR decompostion
    householder(A2, R2, Q2);

    cout << "--- QRD results calculated from Arm core ---" << endl;

    matrix_show(Q2,"Q2:");
    matrix_show(R2,"R2:");

    // compare Q*R to the original matrix A
//    Matrix A_check;
//    A_check.mult(Q, R);
//
//    // compute L2 norm ||A-A_check||^2
//    double l2 = matrix_compare(A,A_check);

    // display Q*R
    //matrix_show(A_check, l2 < 1e-12 ? "A == Q * R ? yes" : "A == Q * R ? no");

	cout << "--- End of the Program ---" << endl;


	// inputs
//	THETA_TYPE a11 = 0.8799;
//	THETA_TYPE a21 = 0.3401;
//	THETA_TYPE a31 = 0.3784;
//	THETA_TYPE a41 = 0.6900;
//
//	THETA_TYPE a12 = 0.3194;
//	THETA_TYPE a22 = 0.8434;
//	THETA_TYPE a32 = 0.2577;
//	THETA_TYPE a42 = 0.5054;
//
//	THETA_TYPE a13 = 0.9805;
//	THETA_TYPE a23 = 0.0687;
//	THETA_TYPE a33 = 0.2073;
//	THETA_TYPE a43 = 0.5914;
//
//	THETA_TYPE a14 = 0.0850;
//	THETA_TYPE a24 = 0.4099;
//	THETA_TYPE a34 = 0.6262;
//	THETA_TYPE a44 = 0.5547;
//	bool rst;
//	bool start;
//	rst = false;
//	start = false;
//	//cout << "\n a11:" << a11 << ",  a12: " << a12 << ",  a13: " << a13 << ",  a14:" << a14 << endl;
//	//cout << "\n ua11:" << ua11 << ",  ua12: " << ua21 << ",  ua13: " << ua31 << ",  a14:" << ua41 << endl;
//
//	signed int ua11 = get_int_reinterpret(a11);
//	signed int ua21 = get_int_reinterpret(a21);
//	signed int ua31 = get_int_reinterpret(a31);
//	signed int ua41 = get_int_reinterpret(a41);
//
//	signed int ua12 = get_int_reinterpret(a12);
//	signed int ua22 = get_int_reinterpret(a22);
//	signed int ua32 = get_int_reinterpret(a32);
//	signed int ua42 = get_int_reinterpret(a42);
//
//
//	signed int ua13 = get_int_reinterpret(a13);
//	signed int ua23 = get_int_reinterpret(a23);
//	signed int ua33 = get_int_reinterpret(a33);
//	signed int ua43 = get_int_reinterpret(a43);
//
//	signed int ua14 = get_int_reinterpret(a14);
//	signed int ua24 = get_int_reinterpret(a24);
//	signed int ua34 = get_int_reinterpret(a34);
//	signed int ua44 = get_int_reinterpret(a44);
//
//
//	//
//	signed int uor11, uor12, uor13, uor14;
//	signed int        uor22, uor32, uor24;
//	signed int  	         uor33, uor34;
//	signed int 				        uor44;
//
//	signed int uoq11, uoq21, uoq31, uoq41;
//	signed int uoq12, uoq22, uoq32, uoq42;
//	signed int uoq13, uoq23, uoq33, uoq43;
//	signed int uoq14, uoq24, uoq34, uoq44;
//
//
//	THETA_TYPE or11, or21, or31, or41;
//	THETA_TYPE or12, or22, or32, or42;
//	THETA_TYPE or13, or23, or33, or43;
//	THETA_TYPE or14, or24, or34, or44;
//
//	THETA_TYPE oq11, oq21, oq31, oq41;
//	THETA_TYPE oq12, oq22, oq32, oq42;
//	THETA_TYPE oq13, oq23, oq33, oq43;
//	THETA_TYPE oq14, oq24, oq34, oq44;
//
//
//	//	XCordic_Initialize(&Cordic, 0)
//	arm_core_design_block_Initialize(&Arm_core_design_block, 0);
//
//
//	arm_core_design_block_a11_var_write(&Arm_core_design_block, ua11);
//	arm_core_design_block_a21_var_write(&Arm_core_design_block, ua21);
//	arm_core_design_block_a31_var_write(&Arm_core_design_block, ua31);
//	arm_core_design_block_a41_var_write(&Arm_core_design_block, ua41);
//
//	arm_core_design_block_a12_var_write(&Arm_core_design_block, ua12);
//	arm_core_design_block_a22_var_write(&Arm_core_design_block, ua22);
//	arm_core_design_block_a32_var_write(&Arm_core_design_block, ua32);
//	arm_core_design_block_a42_var_write(&Arm_core_design_block, ua42);
//
//	arm_core_design_block_a13_var_write(&Arm_core_design_block, ua13);
//	arm_core_design_block_a23_var_write(&Arm_core_design_block, ua23);
//	arm_core_design_block_a33_var_write(&Arm_core_design_block, ua33);
//	arm_core_design_block_a43_var_write(&Arm_core_design_block, ua43);
//
//
//	arm_core_design_block_a14_var_write(&Arm_core_design_block, ua14);
//	arm_core_design_block_a24_var_write(&Arm_core_design_block, ua24);
//	arm_core_design_block_a34_var_write(&Arm_core_design_block, ua34);
//	arm_core_design_block_a44_var_write(&Arm_core_design_block, ua44);
//
//	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);
//
//	delay_ms(100);
//	arm_core_design_block_rst_var_write(&Arm_core_design_block, false);
//	arm_core_design_block_start_var_write(&Arm_core_design_block, false);
//
//	delay_ms(500);
//	arm_core_design_block_start_var_write(&Arm_core_design_block, true);
//
//	delay_ms(5000);
//	//sleep
//	//	R matrix
//	uor11 = arm_core_design_block_rout_11_read(&Arm_core_design_block);
//
//	uor12 = arm_core_design_block_rout_21_read(&Arm_core_design_block);
//	uor22 = arm_core_design_block_rout_22_read(&Arm_core_design_block);
//
//	uor13 = arm_core_design_block_rout_31_read(&Arm_core_design_block);
//	uor32 = arm_core_design_block_rout_32_read(&Arm_core_design_block);
//	uor33 = arm_core_design_block_rout_33_read(&Arm_core_design_block);
//
//	uor14 = arm_core_design_block_rout_41_read(&Arm_core_design_block);
//	uor24 = arm_core_design_block_rout_42_read(&Arm_core_design_block);
//	uor34 = arm_core_design_block_rout_43_read(&Arm_core_design_block);
//	uor44 = arm_core_design_block_rout_44_read(&Arm_core_design_block);
//
//	//	Q matrix
//	uoq11 = arm_core_design_block_qout_11_read(&Arm_core_design_block);
//	uoq12 = arm_core_design_block_qout_12_read(&Arm_core_design_block);
//	uoq13 = arm_core_design_block_qout_13_read(&Arm_core_design_block);
//	uoq14 = arm_core_design_block_qout_14_read(&Arm_core_design_block);
//
//	uoq21 = arm_core_design_block_qout_21_read(&Arm_core_design_block);
//	uoq22 = arm_core_design_block_qout_22_read(&Arm_core_design_block);
//	uoq23 = arm_core_design_block_qout_23_read(&Arm_core_design_block);
//	uoq24 = arm_core_design_block_qout_24_read(&Arm_core_design_block);
//
//	uoq31 = arm_core_design_block_qout_31_read(&Arm_core_design_block);
//	uoq32 = arm_core_design_block_qout_32_read(&Arm_core_design_block);
//	uoq33 = arm_core_design_block_qout_33_read(&Arm_core_design_block);
//	uoq34 = arm_core_design_block_qout_34_read(&Arm_core_design_block);
//
//	uoq41 = arm_core_design_block_qout_41_read(&Arm_core_design_block);
//	uoq42 = arm_core_design_block_qout_42_read(&Arm_core_design_block);
//	uoq43 = arm_core_design_block_qout_43_read(&Arm_core_design_block);
//	uoq44 = arm_core_design_block_qout_44_read(&Arm_core_design_block);
//
//
//
//
//
//	//	  R out
//	or11 = get_fixed_reinterpret(uor11);
//
//	or12 = get_fixed_reinterpret(uor12);
//	or22 = get_fixed_reinterpret(uor22);
//
//	or13 = get_fixed_reinterpret(uor13);
//	or23 = get_fixed_reinterpret(uor32);
//	or33 = get_fixed_reinterpret(uor33);
//
//	or14 = get_fixed_reinterpret(uor14);
//	or24 = get_fixed_reinterpret(uor24);
//	or34 = get_fixed_reinterpret(uor34);
//	or44 = get_fixed_reinterpret(uor44);
//
//	//Q output
//	oq11 = get_fixed_reinterpret(uoq11);
//	oq12 = get_fixed_reinterpret(uoq12);
//	oq13 = get_fixed_reinterpret(uoq13);
//	oq14 = get_fixed_reinterpret(uoq14);
//
//	oq21 = get_fixed_reinterpret(uoq21);
//	oq22 = get_fixed_reinterpret(uoq22);
//	oq23 = get_fixed_reinterpret(uoq23);
//	oq24 = get_fixed_reinterpret(uoq24);
//
//	oq31 = get_fixed_reinterpret(uoq31);
//	oq32 = get_fixed_reinterpret(uoq32);
//	oq33 = get_fixed_reinterpret(uoq33);
//	oq34 = get_fixed_reinterpret(uoq34);
//
//	oq41 = get_fixed_reinterpret(uoq41);
//	oq42 = get_fixed_reinterpret(uoq42);
//	oq43 = get_fixed_reinterpret(uoq43);
//	oq44 = get_fixed_reinterpret(uoq44);
//
//
//	cout << "--------------------Praying for it working MODE--------------------" << endl;
//
//
//
//	or21 = 0.00000;
//	or31 = 0.00000; or32 = 0.00000;
//	or41 = 0.00000; or42 = 0.00000;  or43 = 0.00000;
//
//
//	cout << "\n--------------------A1--------------------" << endl;
//	cout << "\n {" << a11 << ", " << a12 << ", " << a13 << ", " << a14 << "}, " << endl;
//	cout << "\n {" << a21 << ", " << a22 << ", " << a23 << ", " << a24 << "}, " << endl;
//	cout << "\n {" << a31 << ", " << a32 << ", " << a33 << ", " << a34 << "}, " << endl;
//	cout << "\n {" << a41 << ", " << a42 << ", " << a43 << ", " << a44 << "}} " << endl;
//
//
//	cout << "--------------------R1--------------------" << endl;
//
//	cout << "\n {" << or11 << ", " << or12 << ", " << or13 << ", " << or14 << "}, " << endl;
//	cout << "\n {0.00000," << or22 << ", " << or23 << ", " << or24 << "}, " << endl;
//	cout << "\n {0.00000, 0.00000, " << or33 << ", " << or34 << "}, " << endl;
//	cout << "\n {0.00000, 0.00000, 0.00000, " << or44 << "}} " << endl;
//
//	cout << "--------------------Q1--------------------" << endl;
//
//	cout << "\n {" << oq11 << ", " << oq21 << ", " << oq31 << ", " << oq41 << "}, " << endl;
//	cout << "\n {" << oq12 << ", " << oq22 << ", " << oq32 << ", " << oq42 << "}, " << endl;
//	cout << "\n {" << oq13 << ", " << oq23 << ", " << oq33 << ", " << oq43 << "}, " << endl;
//	cout << "\n {" << oq14 << ", " << oq24 << ", " << oq34 << ", " << oq44 << "}} " << endl;
//
//
//	cout << "\n --------------------*Next Matrix*--------------------" << endl;
//
//
//
//	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);
//
//	a11 = 0.1845;
//	a21 = 0.6496;
//	a31 = 0.1345;
//	a41 = 0.9629;
//
//	a12 = 0.7026;
//	a22 = 0.9629;
//	a32 = 0.5616;
//	a42 = 0.2118;
//
//	a13 = 0.7124;
//	a23 = 0.7813;
//	a33 = 0.1008;
//	a43 = 0.8349;
//
//	a14 = 0.6811;
//	a24 = 0.9637;
//	a34 = 0.9517;
//	a44 = 0.4713;
//
//	ua11 = get_int_reinterpret(a11);
//	ua21 = get_int_reinterpret(a21);
//	ua31 = get_int_reinterpret(a31);
//	ua41 = get_int_reinterpret(a41);
//
//	ua12 = get_int_reinterpret(a12);
//	ua22 = get_int_reinterpret(a22);
//	ua32 = get_int_reinterpret(a32);
//	ua42 = get_int_reinterpret(a42);
//
//	ua13 = get_int_reinterpret(a13);
//	ua23 = get_int_reinterpret(a23);
//	ua33 = get_int_reinterpret(a33);
//	ua43 = get_int_reinterpret(a43);
//
//	ua14 = get_int_reinterpret(a14);
//	ua24 = get_int_reinterpret(a24);
//	ua34 = get_int_reinterpret(a34);
//	ua44 = get_int_reinterpret(a44);
//
//
//	delay_ms(200);
//
//	arm_core_design_block_a11_var_write(&Arm_core_design_block, ua11);
//	arm_core_design_block_a21_var_write(&Arm_core_design_block, ua21);
//	arm_core_design_block_a31_var_write(&Arm_core_design_block, ua31);
//	arm_core_design_block_a41_var_write(&Arm_core_design_block, ua41);
//
//	arm_core_design_block_a12_var_write(&Arm_core_design_block, ua12);
//	arm_core_design_block_a22_var_write(&Arm_core_design_block, ua22);
//	arm_core_design_block_a32_var_write(&Arm_core_design_block, ua32);
//	arm_core_design_block_a42_var_write(&Arm_core_design_block, ua42);
//
//	arm_core_design_block_a13_var_write(&Arm_core_design_block, ua13);
//	arm_core_design_block_a23_var_write(&Arm_core_design_block, ua23);
//	arm_core_design_block_a33_var_write(&Arm_core_design_block, ua33);
//	arm_core_design_block_a43_var_write(&Arm_core_design_block, ua43);
//
//
//	arm_core_design_block_a14_var_write(&Arm_core_design_block, ua14);
//	arm_core_design_block_a24_var_write(&Arm_core_design_block, ua24);
//	arm_core_design_block_a34_var_write(&Arm_core_design_block, ua34);
//	arm_core_design_block_a44_var_write(&Arm_core_design_block, ua44);
//
//	arm_core_design_block_rst_var_write(&Arm_core_design_block, true);
//
//	delay_ms(100);
//	arm_core_design_block_rst_var_write(&Arm_core_design_block, false);
//	arm_core_design_block_start_var_write(&Arm_core_design_block, false);
//
//	delay_ms(500);
//	arm_core_design_block_start_var_write(&Arm_core_design_block, true);
//
//	delay_ms(5000);
//	//sleep
//	//	R matrix
//	uor11 = arm_core_design_block_rout_11_read(&Arm_core_design_block);
//
//	uor12 = arm_core_design_block_rout_21_read(&Arm_core_design_block);
//	uor22 = arm_core_design_block_rout_22_read(&Arm_core_design_block);
//
//	uor13 = arm_core_design_block_rout_31_read(&Arm_core_design_block);
//	uor32 = arm_core_design_block_rout_32_read(&Arm_core_design_block);
//	uor33 = arm_core_design_block_rout_33_read(&Arm_core_design_block);
//
//	uor14 = arm_core_design_block_rout_41_read(&Arm_core_design_block);
//	uor24 = arm_core_design_block_rout_42_read(&Arm_core_design_block);
//	uor34 = arm_core_design_block_rout_43_read(&Arm_core_design_block);
//	uor44 = arm_core_design_block_rout_44_read(&Arm_core_design_block);
//
//	//Q matrix
//	uoq11 = arm_core_design_block_qout_11_read(&Arm_core_design_block);
//	uoq12 = arm_core_design_block_qout_12_read(&Arm_core_design_block);
//	uoq13 = arm_core_design_block_qout_13_read(&Arm_core_design_block);
//	uoq14 = arm_core_design_block_qout_14_read(&Arm_core_design_block);
//
//	uoq21 = arm_core_design_block_qout_21_read(&Arm_core_design_block);
//	uoq22 = arm_core_design_block_qout_22_read(&Arm_core_design_block);
//	uoq23 = arm_core_design_block_qout_23_read(&Arm_core_design_block);
//	uoq24 = arm_core_design_block_qout_24_read(&Arm_core_design_block);
//
//	uoq31 = arm_core_design_block_qout_31_read(&Arm_core_design_block);
//	uoq32 = arm_core_design_block_qout_32_read(&Arm_core_design_block);
//	uoq33 = arm_core_design_block_qout_33_read(&Arm_core_design_block);
//	uoq34 = arm_core_design_block_qout_34_read(&Arm_core_design_block);
//
//	uoq41 = arm_core_design_block_qout_41_read(&Arm_core_design_block);
//	uoq42 = arm_core_design_block_qout_42_read(&Arm_core_design_block);
//	uoq43 = arm_core_design_block_qout_43_read(&Arm_core_design_block);
//	uoq44 = arm_core_design_block_qout_44_read(&Arm_core_design_block);
//
//
//
//
//
//	//R out
//	or11 = get_fixed_reinterpret(uor11);
//
//	or12 = get_fixed_reinterpret(uor12);
//	or22 = get_fixed_reinterpret(uor22);
//
//	or13 = get_fixed_reinterpret(uor13);
//	or23 = get_fixed_reinterpret(uor32);
//	or33 = get_fixed_reinterpret(uor33);
//
//	or14 = get_fixed_reinterpret(uor14);
//	or24 = get_fixed_reinterpret(uor24);
//	or34 = get_fixed_reinterpret(uor34);
//	or44 = get_fixed_reinterpret(uor44);
//
//	//Q output
//	oq11 = get_fixed_reinterpret(uoq11);
//	oq12 = get_fixed_reinterpret(uoq12);
//	oq13 = get_fixed_reinterpret(uoq13);
//	oq14 = get_fixed_reinterpret(uoq14);
//
//	oq21 = get_fixed_reinterpret(uoq21);
//	oq22 = get_fixed_reinterpret(uoq22);
//	oq23 = get_fixed_reinterpret(uoq23);
//	oq24 = get_fixed_reinterpret(uoq24);
//
//	oq31 = get_fixed_reinterpret(uoq31);
//	oq32 = get_fixed_reinterpret(uoq32);
//	oq33 = get_fixed_reinterpret(uoq33);
//	oq34 = get_fixed_reinterpret(uoq34);
//
//	oq41 = get_fixed_reinterpret(uoq41);
//	oq42 = get_fixed_reinterpret(uoq42);
//	oq43 = get_fixed_reinterpret(uoq43);
//	oq44 = get_fixed_reinterpret(uoq44);
//
//
//
//	cout << "\n--------------------A2--------------------" << endl;
//
//	cout << "\n {" << a11 << ", " << a12 << ", " << a13 << ", " << a14 << "}, " << endl;
//	cout << "\n {" << a21 << ", " << a22 << ", " << a23 << ", " << a24 << "}, " << endl;
//	cout << "\n {" << a31 << ", " << a32 << ", " << a33 << ", " << a34 << "}, " << endl;
//	cout << "\n {" << a41 << ", " << a42 << ", " << a43 << ", " << a44 << "}} " << endl;
//
//
//
//	cout << "\n--------------------R2--------------------" << endl;
//
//	cout << "\n {" << or11 << ", " << or12 << ", " << or13 << ", " << or14 << "}, " << endl;
//	cout << "\n {0.00000," << or22 << ", " << or23 << ", " << or24 << "}, " << endl;
//	cout << "\n {0.00000, 0.00000, " << or33 << ", " << or34 << "}, " << endl;
//	cout << "\n {0.00000, 0.00000, 0.00000, " << or44 << "}} " << endl;
//
//	cout << "--------------------Q2--------------------" << endl;
//
//	cout << "\n {" << oq11 << ", " << oq21 << ", " << oq31 << ", " << oq41 << "}, " << endl;
//	cout << "\n {" << oq12 << ", " << oq22 << ", " << oq32 << ", " << oq42 << "}, " << endl;
//	cout << "\n {" << oq13 << ", " << oq23 << ", " << oq33 << ", " << oq43 << "}, " << endl;
//	cout << "\n {" << oq14 << ", " << oq24 << ", " << oq34 << ", " << oq44 << "}} " << endl;






















	//	cout << "\nor11 " << or11 << or21 << or31 << or41 << endl;
	//reinterpret
	// values for simulation and testing using C++ format with ap_fixed
	//inputs	COS_SIN_TYPE x;COS_SIN_TYPE y;	THETA_TYPE theta;	bool state;
	//outputs	COS_SIN_TYPE c;	COS_SIN_TYPE s;	COS_SIN_TYPE t;
	//	THETA_TYPE a_in = 1.2;
	// values for sending over AXI bus to programmable logic (PL)
	//signed int state_u32, theta_u32, x_u32, y_u32, s_out_u32, c_out_u32, t_out_u32;
	//void cordic(bool state, THETA_TYPE theta, COS_SIN_TYPE x, COS_SIN_TYPE y, COS_SIN_TYPE &s, COS_SIN_TYPE &c, THETA_TYPE_in &t);
	//sin/cos mode


	/*x = 1; 	y = 0; 	state = true; 	int angle = 0; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {    s_out_u32 = XCordic_Get_s(&Cordic);    c_out_u32 = XCordic_Get_c(&Cordic);    t_out_u32 = XCordic_Get_t(&Cordic);}
	while (!XCordic_IsReady(&Cordic));  while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32); 	s = get_fixed_reinterpret(s_out_u32);  c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32);
	cout  << "\nState: "<< state <<",  x: "<< x << ",  y: " << y << ",  Theta_in:" << angle <<", cos: " << c << ",  sin: " << s << ",  theta_out: "<< t << endl;

	x = 1; 	y = 0; 	state = true;  angle = 15; theta = angle*M_PI/180;
	x_u32 = get_int_reinterpret(x);	y_u32 = get_int_reinterpret(y); state_u32 = get_int_reinterpret(state); XCordic_Initialize(&Cordic, 0);
	XCordic_Set_x(&Cordic, x_u32);	XCordic_Set_y(&Cordic, y_u32); 	XCordic_Set_state(&Cordic, state);
	theta_u32 = get_int_reinterpret(theta); 	XCordic_Set_theta(&Cordic, theta_u32);   XCordic_Start(&Cordic);
	do {  t_out_u32 = XCordic_Get_t(&Cordic);   c_out_u32 = XCordic_Get_c(&Cordic); s_out_u32 = XCordic_Get_s(&Cordic);      }
	while (!XCordic_IsReady(&Cordic));
	s = get_fixed_reinterpret(s_out_u32);
	s = get_fixed_reinterpret(s_out_u32);
	c = get_fixed_reinterpret(c_out_u32);	t = get_fixed_reinterpret(t_out_u32); */


	return 0;
}








