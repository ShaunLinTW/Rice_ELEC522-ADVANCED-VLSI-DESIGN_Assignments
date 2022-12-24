#include "systolicmul.h"

int main(int argc, char **argv) {

   DTYPE in_a_cols_mat[SIZE][SIZE] = {
      {1, 2, 3, 4},
      {5, 6, 7, 8},
      {9, 10, 11, 12},
	  {13, 14, 15, 16}
   };

   DTYPE in_b_rows_mat[SIZE][SIZE] = {
      {1, 0, 2, 0},
      {0, 1, 84, 0},
      {0, 0, 1, 0},
	  {0, 0, 0, 1}
   };

   DTYPE out_c_cols_mat[SIZE][SIZE];

   DTYPE ref_c_cols_mat[SIZE][SIZE];
   for (int i = 0; i < SIZE; i++) {
	   for (int j = 0; j < SIZE; j++) {
		   ref_c_cols_mat[i][j] = 0;
		   for (int k = 0; k < SIZE; k++) {
			   ref_c_cols_mat[i][j] += in_a_cols_mat[i][k] * in_b_rows_mat[k][j];
		   }
	   }
   }

   hls::stream<sizevec> in_a_cols("in_a_cols");
   hls::stream<sizevec> in_b_rows("in_b_rows");
   hls::stream<sizevec> out_c_cols("out_c_cols");

   for (int i = 0; i < 3 * SIZE - 1; i++) {
	   sizevec in_b_row;
	   for (int j = 0; j < SIZE; j++) {
		   int offset = i - j;
		   if (offset >= 0 && offset < SIZE) {
			   in_b_row.data[j] = in_b_rows_mat[offset][j];
		   }
		   else {
			   in_b_row.data[j] = 0;
		   }
	   }
	   in_b_rows.write(in_b_row);
   }

   for (int j = 0; j < 3 * SIZE - 1; j++) {
	   sizevec in_a_col;
	   for (int i = 0; i < SIZE; i++) {
		   int offset = j - i;
		   if (offset >= 0 && offset < SIZE) {
			   in_a_col.data[i] = in_a_cols_mat[i][offset];
		   }
		   else {
			   in_a_col.data[i] = 0;
		   }
	   }
	   in_a_cols.write(in_a_col);
   }

   for (int iteration = 0; iteration < 3 * SIZE - 1; iteration++) {
	   systolicmul(in_a_cols, in_b_rows, out_c_cols, iteration);
   }

   for (int j = 0; j < SIZE; j++) {out_c_cols.read();}

   for (int j = 0; j < 2 * SIZE - 1; j++) {
	   sizevec out_c_col = out_c_cols.read();
	   for (int i = 0; i < SIZE; i++) {
		   int offset = j - i;
		   if (offset >= 0 && offset < SIZE) {
			   out_c_cols_mat[i][offset] = out_c_col.data[i];
		   }
	   }
   }

   bool ok = true;
   for (int i = 0; i < SIZE; i++) {
	   for (int j = 0; j < SIZE; j++) {
		   printf("%i ", out_c_cols_mat[i][j]);
		   ok = ok && (out_c_cols_mat[i][j] == ref_c_cols_mat[i][j]);
	   }
	   printf("\n");
   }
   if (ok) {
	   printf("Test succeeded!\n");
   }
   else {
	   printf("Test failed!\n");
   }

}

