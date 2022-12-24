#include "systolicmul.h"

void systolicmul(hls::stream<sizevec> &in_a_cols, hls::stream<sizevec> &in_b_rows, hls::stream<sizevec> &out_c_cols, uint32_t iteration) {

	#pragma HLS PIPELINE II=1

	static DTYPE state_a[SIZE][SIZE - 1];
	static DTYPE state_b[SIZE - 1][SIZE];
	static DTYPE state_c[SIZE][SIZE];

	sizevec in_a_col = in_a_cols.read();
	sizevec in_b_row = in_b_rows.read();
	sizevec out_c_col;

	i_loop: for(int i = SIZE - 1; i >= 0; i--) {
		j_loop: for(int j = SIZE - 1; j >= 0; j--) {
			DTYPE mulop_a;
			DTYPE mulop_b;
			if (i == 0) {
				mulop_b = in_b_row.data[j];
			}
			else {
				mulop_b = state_b[i-1][j];
			}
			if (j == 0) {
				mulop_a = in_a_col.data[i];
			}
			else {
				mulop_a = state_a[i][j-1];
			}

			DTYPE product = mulop_a * mulop_b;
			if ((iteration % SIZE) == ((i + j) % SIZE)) {
				out_c_col.data[i] = state_c[i][j];
				state_c[i][j] = product;
			}
			else {
				state_c[i][j] += product;
			}

			if (i < SIZE - 1) {
				state_b[i][j] = mulop_b;
			}
			if (j < SIZE - 1) {
				state_a[i][j] = mulop_a;
			}
		}
	}

	out_c_cols.write(out_c_col);

}
