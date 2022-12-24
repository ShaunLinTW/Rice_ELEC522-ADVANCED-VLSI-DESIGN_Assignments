#include "matmul.h"

void MVM(
		hls::stream<v_t>& inStreamA,
		hls::stream<m_t>& inStreamB,
		hls::stream<v_t>& outStream
		) {

	v_t aVec;
	m_t bMat;
	v_t sVec;
	inStreamA >> aVec;
	inStreamB >> bMat;
	MVM_label0:for (int i = 0; i <= 3; i++) {
		v_t pVec = aVec * bMat[i];
		d_t p1 = pVec[0] + pVec[1];
		d_t p2 = pVec[2] + pVec[3];
		d_t pf = p1 + p2;
		sVec[i] = pf;
	}
	outStream << sVec;
}





void VVM(
		hls::stream<v_t>& inStreamA,
		hls::stream<v_t>& inStreamB,
		hls::stream<d_t>& outStream
		) {

	v_t aVec;
	v_t bVec;
	inStreamA >> aVec;
	inStreamB >> bVec;
	v_t pVec = aVec * bVec;
	d_t p1 = pVec[0] + pVec[1];
	d_t p2 = pVec[2] + pVec[3];
	d_t pf = p1 + p2;
	outStream << pf;
}
