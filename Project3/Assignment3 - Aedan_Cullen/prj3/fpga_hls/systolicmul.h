#ifndef __SYSTOLICMUL_H__
#define __SYSTOLICMUL_H__
#include "ap_axi_sdata.h"
#include "hls_stream.h"
#include <iostream>
#include <iomanip>
#include <vector>
using namespace std;

typedef uint16_t DTYPE;
typedef hls::stream<hls::axis<DTYPE, 0, 0, 0>> STREAMTYPE;
const int SIZE = 4;

typedef struct {
	DTYPE data[SIZE];
} sizevec;

void systolicmul(hls::stream<sizevec> &in_a_cols, hls::stream<sizevec> &in_b_rows, hls::stream<sizevec> &out_c_cols, uint32_t iteration);

#endif // __SYSTOLICMUL_H__
