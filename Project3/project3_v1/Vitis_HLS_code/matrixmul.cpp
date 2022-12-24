//*****************************************************************************

#include "matrixmul.h"

// The following diagram explains how the matrix multiply happens
//
//        b_1        b_2        b_3        b_4
//         |          |          |          |
//         v          v          v          v
//        ___        ___        ___        ___
//       |   |      |   |      |   |      |   |
//  a1_->|c11| ---- |c12| ---- |c13| ---- |c14|->_res1
//       |___|      |___|      |___|      |___|
//         |          |          |          |
//        ___        ___        ___        ___
//       |   |      |   |      |   |      |   |
//  a2_->|c21| ---- |c22| ---- |c23| ---- |c24|->_res2
//       |___|      |___|      |___|      |___|
//         |          |          |          |
//        ___        ___        ___        ___
//       |   |      |   |      |   |      |   |
//  a3_->|c31| ---- |c32| ---- |c33| ---- |c34|->_res3
//       |___|      |___|      |___|      |___|
//         |          |          |          |
//        ___        ___        ___        ___
//       |   |      |   |      |   |      |   |
//  a4_->|c41| ---- |c42| ---- |c43| ---- |c44|->_res4
//       |___|      |___|      |___|      |___|

void matrixmul(
      mat_a_t a[MAT_A_ROWS][MAT_A_COLS],
      mat_b_t b[MAT_B_ROWS][MAT_B_COLS],
      result_t res[MAT_A_ROWS][MAT_B_COLS])
{
  // Iterate over the rows of the A matrix
  Row: for(int i = 0; i < MAT_A_ROWS; i++) {
    // Iterate over the columns of the B matrix
    Col: for(int j = 0; j < MAT_B_COLS; j++) {
      // Do the inner product of a row of A and col of B
      res[i][j] = 0;
      Product: for(int k = 0; k < MAT_B_ROWS; k++) {
    	  res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
}
