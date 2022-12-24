#include <ap_fixed.h>
#include <hls_vector.h>
#include <hls_stream.h>
#include <cmath>
using namespace std;

#define MAT_DIM 4

typedef ap_fixed<16, 5> d_t;
typedef hls::vector<d_t, 4> v_t;
typedef hls::vector<v_t, 4> m_t;

const d_t const0 = 0.0;

void VVM(
		hls::stream<v_t>& inStreamA,
		hls::stream<v_t>& inStreamB,
		hls::stream<d_t>& outStream
		);
