//*****************************************************************************
//
//*****************************************************************************
//Device: All
//Design Name: treeadd
//Purpose:
//    This is the header for the treeadd.cpp design for Vitis HLS.
//Reference:
//Revision History: October 5, 2022
//*****************************************************************************


#include <cmath>
using namespace std;

// Uncomment this line to compare TB vs HW C-model and/or RTL
// #define HW_COSIM

// Prototype of top level function for C-synthesis
// Variable a through h are inputs. In C language format, a pointer to 
// variable r is passed in so that r can be written in this function.

void treeadd (
	short a, 
	short b, 
	short c, 
	short d, 
	short e, 
	short f, 
	short g, 
	short h, 
	short *r
	);
