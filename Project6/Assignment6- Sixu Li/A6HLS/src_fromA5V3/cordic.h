
#ifndef CORDIC_H
#define CORDIC_H
#include "ap_fixed.h"

typedef ap_fixed<24,8> FIXDT;

const int NUM_ITERATIONS=10;

void cordic(bool select, FIXDT xi, FIXDT yi, FIXDT ti, FIXDT &xo, FIXDT &yo, FIXDT &to);

void qr(
    FIXDT a11, FIXDT a12, FIXDT a13, FIXDT a14, 
    FIXDT a21, FIXDT a22, FIXDT a23, FIXDT a24, 
    FIXDT a31, FIXDT a32, FIXDT a33, FIXDT a34, 
    FIXDT a41, FIXDT a42, FIXDT a43, FIXDT a44,

    FIXDT &q11, FIXDT &q12, FIXDT &q13, FIXDT &q14, 
    FIXDT &q21, FIXDT &q22, FIXDT &q23, FIXDT &q24, 
    FIXDT &q31, FIXDT &q32, FIXDT &q33, FIXDT &q34, 
    FIXDT &q41, FIXDT &q42, FIXDT &q43, FIXDT &q44,

    FIXDT &r11, FIXDT &r12, FIXDT &r13, FIXDT &r14, 
                FIXDT &r22, FIXDT &r23, FIXDT &r24, 
                            FIXDT &r33, FIXDT &r34, 
                                        FIXDT &r44,
	FIXDT din, FIXDT &done
    );

void LinearSolver(
	FIXDT a11, FIXDT a12, FIXDT a13, FIXDT a14,
	FIXDT a21, FIXDT a22, FIXDT a23, FIXDT a24,
	FIXDT a31, FIXDT a32, FIXDT a33, FIXDT a34,
	FIXDT a41, FIXDT a42, FIXDT a43, FIXDT a44,
	FIXDT  b1, FIXDT  b2, FIXDT  b3, FIXDT  b4,

	FIXDT &x1, FIXDT &x2, FIXDT &x3, FIXDT &x4
);
#endif
