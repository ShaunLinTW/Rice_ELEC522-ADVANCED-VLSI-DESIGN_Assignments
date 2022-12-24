//*****************************************************************************
//
//*****************************************************************************
//Design Name: treeadd
//Purpose:
//    This is a C++ version of the treeadd Sysgen example.
//Reference:
//Revision History: Oct. 4, 2018
//*****************************************************************************

#include <cmath>
#include "treeadd.h"


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
	)

{
  // Add the elements into the result r with writing value to pointer of r passed in
  *r = a + b + c + d + e + f + g + h;
  
}


