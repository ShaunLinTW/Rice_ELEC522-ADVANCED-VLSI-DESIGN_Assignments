//*****************************************************************************
//*****************************************************************************
//Device: All
//Design Name: treeadd
//Purpose:
//    This is the C++ test bench for the of a treeadd example in Vitis HLS.
//Reference:
//Revision History: October 5, 2022
//*****************************************************************************
#include <cmath>
#include <iostream>
#include "treeadd.h"

using namespace std;

int main()
{
	short a_in = 2;
	short b_in = 2;
	short c_in = 3;
	short d_in = 4;
	short e_in = 5;
	short f_in = 6;
	short g_in = 7;
	short h_in = 8;
	
	short r_sw, r_hw ;
    int err_cnt = 0;

   // Generate the expected result
   // Add the elements into the result r_sw
	r_sw = a_in + b_in + c_in + d_in + e_in + f_in + g_in + h_in;

#ifdef HW_COSIM
   // Run the Vivado HLS block and pass pointer to r_hw to allow writing of variable
   treeadd (a_in, b_in, c_in, d_in, e_in, f_in, g_in, h_in, &r_hw);
#endif

   // Print result r_sw and r_hw
   
#ifdef HW_COSIM
         cout << "software = " << r_sw << endl;
		 cout << "hardware = " << r_hw << endl;
         // Check HW result against SW
         if (r_hw != r_sw) {
            err_cnt++;
            cout << "*" << endl;
         }
#else
         cout << "software = " << r_sw << endl;
#endif
         

#ifdef HW_COSIM
   if (err_cnt)
      cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
   else
      cout << "Test passed." << endl;
#endif
   return err_cnt;
}

