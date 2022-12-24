//*****************************************************************************
// (c) Copyright 2009 - 2012 Xilinx, Inc. All rights reserved.
//
// This file contains confidential and proprietary information
// of Xilinx, Inc. and is protected under U.S. and
// international copyright and other intellectual property
// laws.
//
// DISCLAIMER
// This disclaimer is not a license and does not grant any
// rights to the materials distributed herewith. Except as
// otherwise provided in a valid license issued to you by
// Xilinx, and to the maximum extent permitted by applicable
// law: (1) THESE MATERIALS ARE MADE AVAILABLE "AS IS" AND
// WITH ALL FAULTS, AND XILINX HEREBY DISCLAIMS ALL WARRANTIES
// AND CONDITIONS, EXPRESS, IMPLIED, OR STATUTORY, INCLUDING
// BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, NON-
// INFRINGEMENT, OR FITNESS FOR ANY PARTICULAR PURPOSE; and
// (2) Xilinx shall not be liable (whether in contract or tort,

// liability) for any loss or damage of any kind or nature
// related to, arising under or in connection with these
// materials, including for any direct, or any indirect,
// special, incidental, or consequential loss or damage
// (including loss of data, profits, goodwill, or any type of
// loss or damage suffered as a result of any action brought
// by a third party) even if such damage or loss was
// reasonably foreseeable or Xilinx had been advised of the
// possibility of the same.
//
// CRITICAL APPLICATIONS
// Xilinx products are not designed or intended to be fail-
// safe, or for use in any application requiring fail-safe
// performance, such as life-support or safety devices or
// systems, Class III medical devices, nuclear facilities,
// applications related to the deployment of airbags, or any
// other applications that could lead to death, personal
// injury, or severe property or environmental damage
// (individually and collectively, "Critical
// Applications"). Customer assumes the sole risk and
// liability of any use of Xilinx products in Critical
// Applications, subject only to applicable laws and
// regulations governing limitations on product liability.
//
// THIS COPYRIGHT NOTICE AND DISCLAIMER MUST BE RETAINED AS
// PART OF THIS FILE AT ALL TIMES.
//
//*****************************************************************************
//   ____  ____
//  /   /\/   /
// /___/  \  /    Vendor: Xilinx
// \   \   \/     Version: %version
//  \   \         Application: AutoESL
//  /   /         Filename: matrixmul_test.cpp
// /___/   /\     Date Last Modified: $Date: 2012/3/30 18:53:07 $
// \   \  /  \    Date Created: Fri Mar 30 2012
//  \___\/\___\
//
//Device: All
//Design Name: maxtrixmul1
//Purpose:
//    This is the C++ test bench for the of a matrix multiplier example.
//Reference:
//Revision History:
//*****************************************************************************
#include <iostream>
#include "matrixmul.h"

using namespace std;

int main(int argc, char **argv)
{
   mat_a_t in_mat_a[4][4] = {
      {1, 1, 1, 1},
	  {2, 2, 2, 2},
	  {3, 3, 3, 3},
	  {4, 4, 4, 4}
   };
   mat_b_t in_mat_b[4][4] = {
	  {1, 1, 1, 1},
	  {2, 2, 2, 2},
	  {3, 3, 3, 3},
	  {4, 4, 4, 4}
   };
   result_t hw_result[4][4], sw_result[4][4];
   //short sw_result[4][4];
   result_t_r1 hw_result_1[4];
   result_t_r2 hw_result_2[4];
   result_t_r3 hw_result_3[4];
   result_t_r4 hw_result_4[4];
   int err_cnt = 0;

   for(int i = 0; i < MAT_A_ROWS; i++) {
      for(int j = 0; j < MAT_B_COLS; j++) {
         sw_result[i][j] = 0;

         for(int k = 0; k < MAT_B_ROWS; k++) {
            sw_result[i][j] += in_mat_a[i][k] * in_mat_b[k][j];
         }
      }
   }



#ifdef HW_COSIM
   // Run the AutoESL matrix multiply block
   matrixmul(in_mat_a, in_mat_b, hw_result,
		   hw_result_1,hw_result_2,hw_result_3,hw_result_4);
#endif

   // Print result matrix
   cout << "{" << endl;
   //cout << setw(6);
   for (int i = 0; i < MAT_A_ROWS; i++) {
      cout << "{";
      for (int j = 0; j < MAT_B_COLS; j++) {
#ifdef HW_COSIM
         //cout << hw_result[i][j];
         // Check HW result against SW
         if(i == 0){cout << hw_result_1[j];
         if (hw_result_1[j] != sw_result[i][j]) {
            err_cnt++;
            cout << "*";
         }}
         if(i == 1){cout << hw_result_2[j];
         if (hw_result_2[j] != sw_result[i][j]) {
            err_cnt++;
            cout << "*";
         }}
         if(i == 2){cout << hw_result_3[j];
         if (hw_result_3[j] != sw_result[i][j]) {
            err_cnt++;
            cout << "*";
         }}
         if(i == 3){cout << hw_result_4[j];
         if (hw_result_4[j] != sw_result[i][j]) {
            err_cnt++;
            cout << "*";
         }}
         //if (res1[j] != sw_result[i][j]) {            err_cnt++;            cout << "*";         }
#else
         cout << sw_result[i][j];
#endif
         if (j == MAT_B_COLS - 1)
            cout << "}" << endl;
         else
            cout << ",";
      }
   }
   cout << "}" << endl;

#ifdef HW_COSIM
   if (err_cnt)
      cout << "ERROR: " << err_cnt << " mismatches detected!" << endl;
   else
      cout << "Test passed." << endl;
#endif
   return err_cnt;
}
