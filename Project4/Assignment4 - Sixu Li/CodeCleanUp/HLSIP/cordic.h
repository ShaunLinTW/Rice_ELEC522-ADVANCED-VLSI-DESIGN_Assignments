
#ifndef CORDIC_H
#define CORDIC_H
#include "ap_fixed.h"

typedef unsigned int UINTYPE_12;
typedef ap_fixed<16,2> FIXDT;

const int NUM_ITERATIONS=10;

void cordic(bool select, FIXDT CS_I_T, FIXDT IA_I_A, FIXDT IA_I_B, FIXDT &CS_O_SIN, FIXDT &CS_O_COS, FIXDT &IA_O_IAT,short &done);

#endif
