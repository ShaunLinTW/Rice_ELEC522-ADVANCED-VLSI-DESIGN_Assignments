//*****************************************************************************
//
//*****************************************************************************
//Device: All
//Design Name: t_fixed
//Purpose:
//    This is the header for the treeadd.cpp design.
//Reference:
//Revision History:
//*****************************************************************************

//#ifndef __TREEADD_H__
//#define __TREEADD_H__
//
//#include <cmath>
//#include "ap_fixed.h"
//using namespace std;
//
//// Uncomment this line to compare TB vs HW C-model and/or RTL
//// #define HW_COSIM
//
//// Prototype of top level function for C-synthesis
//// Variable a through h are inputs. In C language format, a pointer to
//// variable r is passed in so that r can be written in this function.
//
//void t_fixed (
//	ap_fixed<16,3> a,
//	ap_fixed<16,3> b,
//	ap_fixed<16,3> c,
//	ap_fixed<16,3> d,
//	ap_fixed<16,3> e,
//	ap_fixed<16,3> f,
//	ap_fixed<16,3> g,
//	ap_fixed<16,3> h,
//	ap_fixed<16,3> *r,
//	short *done
//	);
//
//
//#endif // __TREEADD_H__ not defined


#ifndef CORDIC_H
#define CORDIC_H
#include "ap_fixed.h"

typedef unsigned int UINTYPE_12;
typedef ap_fixed<16,2> FIXDT;

const int NUM_ITERATIONS=10;

void cordic(bool select, FIXDT CS_I_T, FIXDT IA_I_A, FIXDT IA_I_B, FIXDT &CS_O_SIN, FIXDT &CS_O_COS, FIXDT &IA_O_IAT,short &done);

#endif
