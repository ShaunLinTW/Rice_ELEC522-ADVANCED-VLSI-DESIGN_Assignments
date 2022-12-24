#include <ap_fixed.h>
#include <cmath>
using namespace std;

#define MAT_DIM 4

typedef ap_fixed<16, 5> d_t;
const d_t const0 = 0.0;

void matrixmul(
		d_t a[MAT_DIM][MAT_DIM],
		d_t b[MAT_DIM][MAT_DIM],
		d_t res[MAT_DIM][MAT_DIM])
{
//	d_t localA[MAT_DIM][MAT_DIM];
//	#pragma HLS ARRAY_PARTITION variable=localA dim=1 complete
//
//	d_t localB[MAT_DIM][MAT_DIM];
//	#pragma HLS ARRAY_PARTITION variable=localB dim=2 complete

	d_t localC[MAT_DIM][MAT_DIM];
	#pragma HLS ARRAY_PARTITION variable = localC dim = 0 complete

	systolic1:
	    for (int k = 0; k < MAT_DIM; k++) {
	       #pragma HLS LOOP_TRIPCOUNT min=4 max=4
	       #pragma HLS PIPELINE II=1
	    systolic2:
	        for (int i = 0; i < MAT_DIM; i++) {
	        systolic3:
	            for (int j = 0; j < MAT_DIM; j++) {

	            	d_t last = (k == 0) ? const0 : res[i][j];
	                d_t a_val = (i < MAT_DIM && k < MAT_DIM) ? a[i][k] : const0;
	                d_t b_val = (k < MAT_DIM && j < MAT_DIM) ? b[k][j] : const0;
	                d_t result = last + a_val * b_val;

	                localC[i][j] = result;
	            }
	        }
	    }
	for (int i = 0; i < MAT_DIM; i++) {
		for (int j = 0; j < MAT_DIM; j++) {
			res[i][j] = localC[i][j];
		}
	}
}
