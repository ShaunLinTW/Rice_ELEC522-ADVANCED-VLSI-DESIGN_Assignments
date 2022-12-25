#include "cordic.h"

void qr(
    FIXDT a11, FIXDT a12, FIXDT a13, FIXDT a14, 
    FIXDT a21, FIXDT a22, FIXDT a23, FIXDT a24, 
    FIXDT a31, FIXDT a32, FIXDT a33, FIXDT a34, 
    FIXDT a41, FIXDT a42, FIXDT a43, FIXDT a44,

    FIXDT &q11, FIXDT &q12, FIXDT &q13, FIXDT &q14, 
    FIXDT &q21, FIXDT &q22, FIXDT &q23, FIXDT &q24, 
    FIXDT &q31, FIXDT &q32, FIXDT &q33, FIXDT &q34, 
    FIXDT &q41, FIXDT &q42, FIXDT &q43, FIXDT &q44,

    FIXDT &r11, FIXDT &r12, FIXDT &r13, FIXDT &r14, 
                FIXDT &r22, FIXDT &r23, FIXDT &r24, 
                            FIXDT &r33, FIXDT &r34, 
                                        FIXDT &r44,

	FIXDT din, FIXDT &done
    ) {
#pragma HLS INTERFACE s_axilite port=return bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a11 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a21 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a31 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a41 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a12 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a22 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a32 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a42 bundle=HLS_TREEADD_PERIPH_BUS

	#pragma HLS INTERFACE s_axilite port=a13 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a23 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a33 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a43 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a14 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a24 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a34 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=a44 bundle=HLS_TREEADD_PERIPH_BUS


	#pragma HLS INTERFACE s_axilite port=q11 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q21 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q31 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q41 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q12 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q22 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q32 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q42 bundle=HLS_TREEADD_PERIPH_BUS

	#pragma HLS INTERFACE s_axilite port=q13 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q23 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q33 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q43 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q14 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q24 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q34 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=q44 bundle=HLS_TREEADD_PERIPH_BUS


	#pragma HLS INTERFACE s_axilite port=r11 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r12 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r22 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r13 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r23 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r33 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r14 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r24 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r34 bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=r44 bundle=HLS_TREEADD_PERIPH_BUS

	#pragma HLS INTERFACE s_axilite port=din bundle=HLS_TREEADD_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=done bundle=HLS_TREEADD_PERIPH_BUS

	FIXDT sf = (FIXDT) 0.60725;

	FIXDT A[4][4];
	A[0][0] = a11;
	A[0][1] = a21;
	A[0][2] = a31;
	A[0][3] = a41;
	A[1][0] = a12;
	A[1][1] = a22;
	A[1][2] = a32;
	A[1][3] = a42;
	A[2][0] = a13;
	A[2][1] = a23;
	A[2][2] = a33;
	A[2][3] = a43;
	A[3][0] = a14;
	A[3][1] = a24;
	A[3][2] = a34;
	A[3][3] = a44;


    //////////////////////////////////////////////////// R Layer 1
	FIXDT TempV1[5] = {0};
	FIXDT PhaseV1[4] = {0};
	for (int i = 0; i < 4; i++) {
		FIXDT Dummy;
		cordic(0, A[0][i], TempV1[i], 0, TempV1[i+1], Dummy, PhaseV1[i]);
        TempV1[i+1] = TempV1[i+1] * sf;
	}
    r11 = TempV1[4];

	FIXDT TempR1_1[5] = {0};
	FIXDT XOR1_1[4] = {0};
	for (int i = 0; i < 4; i++) {
        FIXDT Dummy;
        cordic(1, TempR1_1[i] * sf, A[1][i] * sf, PhaseV1[i], XOR1_1[i], TempR1_1[i+1], Dummy);
	}
    r12 = TempR1_1[4];

	FIXDT TempR1_2[5] = {0};
	FIXDT XOR1_2[4] = {0};
	for (int i = 0; i < 4; i++) {
		FIXDT Dummy;
        cordic(1, TempR1_2[i] * sf, A[2][i] * sf, PhaseV1[i], XOR1_2[i], TempR1_2[i+1], Dummy);
	}
    r13 = TempR1_2[4];

	FIXDT TempR1_3[5] = {0};
	FIXDT XOR1_3[4] = {0};
	for (int i = 0; i < 4; i++) {
		FIXDT Dummy;
        cordic(1, TempR1_3[i] * sf , A[3][i] * sf, PhaseV1[i], XOR1_3[i], TempR1_3[i+1], Dummy);
	}
    r14 = TempR1_3[4];

     //////////////////////////////////////////////////// R Layer 2
	 FIXDT TempV2[5] = {0};
	 FIXDT PhaseV2[4] = {0};
	 for (int i = 0; i < 4; i++) {
	 	FIXDT Dummy;
	 	cordic(0, TempV2[i], XOR1_1[i], 0, TempV2[i+1], Dummy, PhaseV2[i]);
	 	TempV2[i+1] = TempV2[i+1] * sf;
	 }
	 r22 = TempV2[4];

	 FIXDT TempR2_2[5] = {0};
	 FIXDT XOR2_2[4] = {0};
	 for (int i = 0; i < 4; i++) {
         FIXDT Dummy;
         cordic(1, XOR1_2[i] * sf , TempR2_2[i] * sf, PhaseV2[i], XOR2_2[i], TempR2_2[i+1], Dummy);
	 }
	 r23 = TempR2_2[4];

	 FIXDT TempR2_3[5] = {0};
	 FIXDT XOR2_3[4] = {0};
	 for (int i = 0; i < 4; i++) {
	 	FIXDT Dummy;
         cordic(1, XOR1_3[i] * sf , TempR2_3[i] * sf, PhaseV2[i], XOR2_3[i], TempR2_3[i+1], Dummy);
	 }
	 r24 = TempR2_3[4];

     //////////////////////////////////////////////////// R Layer 3
	 FIXDT TempV3[5] = {0};
	 FIXDT PhaseV3[4] = {0};
	 for (int i = 0; i < 4; i++) {
	 	FIXDT Dummy;
	 	cordic(0, TempV3[i], XOR2_2[i], 0, TempV3[i+1], Dummy, PhaseV3[i]);
	 	TempV3[i+1] = TempV3[i+1] * sf;
	 }
	 r33 = TempV3[4];


	 FIXDT TempR3_3[5] = {0};
	 FIXDT XOR3_3[4] = {0};
	 for (int i = 0; i < 4; i++) {
	 	FIXDT Dummy;
         cordic(1, XOR2_3[i] * sf , TempR3_3[i] * sf, PhaseV3[i], XOR3_3[i], TempR3_3[i+1], Dummy);
	 }
	 r34 = TempR3_3[4];


     //////////////////////////////////////////////////// R Layer 4
	 FIXDT TempV4[5] = {0};
	 FIXDT PhaseV4[4] = {0};
	 for (int i = 0; i < 4; i++) {
	 	FIXDT Dummy;
	 	cordic(0, TempV4[i], XOR3_3[i], 0, TempV4[i+1], Dummy, PhaseV4[i]);
	 	TempV4[i+1] = TempV4[i+1] * sf;
	 }
	 r44 = TempV4[4];



	 /////////////////////////////////////////////////// Q Initialization
	 FIXDT L[4][4];
	 L[0][0] = 1;
	 L[0][1] = 0;
	 L[0][2] = 0;
	 L[0][3] = 0;
	 L[1][0] = 0;
	 L[1][1] = 1;
	 L[1][2] = 0;
	 L[1][3] = 0;
	 L[2][0] = 0;
	 L[2][1] = 0;
	 L[2][2] = 1;
	 L[2][3] = 0;
	 L[3][0] = 0;
	 L[3][1] = 0;
	 L[3][2] = 0;
	 L[3][3] = 1;
	 /////////////////////////////////////////////////// Q Layer 1
	 FIXDT TempQ1_1[5] = {0};
	 FIXDT XOQ1_1[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, TempQ1_1[i] * sf, L[0][i] * sf, PhaseV1[i], XOQ1_1[i], TempQ1_1[i+1], Dummy);
	 }
	 q11 = TempQ1_1[4];

	 FIXDT TempQ1_2[5] = {0};
	 FIXDT XOQ1_2[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, TempQ1_2[i] * sf, L[1][i] * sf, PhaseV1[i], XOQ1_2[i], TempQ1_2[i+1], Dummy);
	 }
	 q12 = TempQ1_2[4];

	 FIXDT TempQ1_3[5] = {0};
	 FIXDT XOQ1_3[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, TempQ1_3[i] * sf, L[2][i] * sf, PhaseV1[i], XOQ1_3[i], TempQ1_3[i+1], Dummy);
	 }
	 q13 = TempQ1_3[4];

	 FIXDT TempQ1_4[5] = {0};
	 FIXDT XOQ1_4[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, TempQ1_4[i] * sf, L[3][i] * sf, PhaseV1[i], XOQ1_4[i], TempQ1_4[i+1], Dummy);
	 }
	 q14 = TempQ1_4[4];

	 /////////////////////////////////////////////////// Q Layer 2
	 FIXDT TempQ2_1[5] = {0};
	 FIXDT XOQ2_1[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ1_1[i] * sf, TempQ2_1[i] * sf, PhaseV2[i], XOQ2_1[i], TempQ2_1[i+1], Dummy);
	 }
	 q21 = TempQ2_1[4];

	 FIXDT TempQ2_2[5] = {0};
	 FIXDT XOQ2_2[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ1_2[i] * sf, TempQ2_2[i] * sf, PhaseV2[i], XOQ2_2[i], TempQ2_2[i+1], Dummy);
	 }
	 q22 = TempQ2_2[4];

	 FIXDT TempQ2_3[5] = {0};
	 FIXDT XOQ2_3[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ1_3[i] * sf, TempQ2_3[i] * sf, PhaseV2[i], XOQ2_3[i], TempQ2_3[i+1], Dummy);
	 }
	 q23 = TempQ2_3[4];

	 FIXDT TempQ2_4[5] = {0};
	 FIXDT XOQ2_4[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ1_4[i] * sf, TempQ2_4[i] * sf, PhaseV2[i], XOQ2_4[i], TempQ2_4[i+1], Dummy);
	 }
	 q24 = TempQ2_4[4];

	 /////////////////////////////////////////////////// Q Layer 3
	 FIXDT TempQ3_1[5] = {0};
	 FIXDT XOQ3_1[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ2_1[i] * sf, TempQ3_1[i] * sf, PhaseV3[i], XOQ3_1[i], TempQ3_1[i+1], Dummy);
	 }
	 q31 = TempQ3_1[4];

	 FIXDT TempQ3_2[5] = {0};
	 FIXDT XOQ3_2[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ2_2[i] * sf, TempQ3_2[i] * sf, PhaseV3[i], XOQ3_2[i], TempQ3_2[i+1], Dummy);
	 }
	 q32 = TempQ3_2[4];

	 FIXDT TempQ3_3[5] = {0};
	 FIXDT XOQ3_3[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ2_3[i] * sf, TempQ3_3[i] * sf, PhaseV3[i], XOQ3_3[i], TempQ3_3[i+1], Dummy);
	 }
	 q33 = TempQ3_3[4];

	 FIXDT TempQ3_4[5] = {0};
	 FIXDT XOQ3_4[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ2_4[i] * sf, TempQ3_4[i] * sf, PhaseV3[i], XOQ3_4[i], TempQ3_4[i+1], Dummy);
	 }
	 q34 = TempQ3_4[4];


	 /////////////////////////////////////////////////// Q Layer 4
	 FIXDT TempQ4_1[5] = {0};
	 FIXDT XOQ4_1[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ3_1[i] * sf, TempQ4_1[i] * sf, PhaseV4[i], XOQ4_1[i], TempQ4_1[i+1], Dummy);
	 }
	 q41 = TempQ4_1[4];

	 FIXDT TempQ4_2[5] = {0};
	 FIXDT XOQ4_2[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ3_2[i] * sf, TempQ4_2[i] * sf, PhaseV4[i], XOQ4_2[i], TempQ4_2[i+1], Dummy);
	 }
	 q42 = TempQ4_2[4];

	 FIXDT TempQ4_3[5] = {0};
	 FIXDT XOQ4_3[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ3_3[i] * sf, TempQ4_3[i] * sf, PhaseV4[i], XOQ4_3[i], TempQ4_3[i+1], Dummy);
	 }
	 q43 = TempQ4_3[4];

	 FIXDT TempQ4_4[5] = {0};
	 FIXDT XOQ4_4[4] = {0};
	 for (int i = 0; i < 4; i++) {
	    FIXDT Dummy;
	    cordic(1, XOQ3_4[i] * sf, TempQ4_4[i] * sf, PhaseV4[i], XOQ4_4[i], TempQ4_4[i+1], Dummy);
	 }
	 q44 = TempQ4_4[4];

	 done = din + 1;
	//  int debugstop = 0;
}
