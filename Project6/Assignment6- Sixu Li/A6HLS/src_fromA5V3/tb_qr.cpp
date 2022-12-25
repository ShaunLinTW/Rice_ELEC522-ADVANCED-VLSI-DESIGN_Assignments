#include "cordic.h"
#include <iostream>

int main() {

    FIXDT a11 = 0.8799, a12 = 0.3194, a13 = 0.9805, a14 = 0.0850; 
    FIXDT a21 = 0.3401, a22 = 0.8438, a23 = 0.0687, a24 = 0.4099; 
    FIXDT a31 = 0.3784, a32 = 0.2577, a33 = 0.2073, a34 = 0.6262; 
    FIXDT a41 = 0.6900, a42 = 0.5054, a43 = 0.5914, a44 = 0.5547;

    FIXDT b1 = 0.8147, b2 = 0.9058, b3 = 0.1270, b4 = 0.9134;

    FIXDT x1, x2, x3, x4;

    FIXDT q11, q12, q13, q14; 
    FIXDT q21, q22, q23, q24; 
    FIXDT q31, q32, q33, q34; 
    FIXDT q41, q42, q43, q44;

    FIXDT r11, r12, r13, r14; 
    FIXDT      r22, r23, r24; 
    FIXDT           r33, r34; 
    FIXDT                r44;

    FIXDT din = 1.5;
    FIXDT done;
    qr(
    a11, a12, a13, a14, 
    a21, a22, a23, a24, 
    a31, a32, a33, a34, 
    a41, a42, a43, a44,
    q11, q12, q13, q14, 
    q21, q22, q23, q24, 
    q31, q32, q33, q34, 
    q41, q42, q43, q44,
    r11, r12, r13, r14, 
         r22, r23, r24, 
              r33, r34, 
                   r44,
	din,done
    );
    std::cout << "------------- QR Test -------------" << std::endl;
    std::cout << "Matrix R: " << std::endl;
    printf("%.4f, %.4f, %.4f, %.4f\n", (float) r11, (float) r12, (float) r13, (float) r14);
    std::cout << r11 << ", " <<  r12 << ", " <<  r13 << ", " <<  r14 << ", " << std::endl;
    printf("%.4f, %.4f, %.4f, %.4f\n", 0.0, (float) r22, (float) r23, (float) r24);
    printf("%.4f, %.4f, %.4f, %.4f\n", 0.0, (float) 0.0, (float) r33, (float) r34);
    printf("%.4f, %.4f, %.4f, %.4f\n", 0.0, (float) 0.0, (float) 0.0, (float) r44);
    std::cout << "Matrix Q: " << std::endl;
    printf("%.4f, %.4f, %.4f, %.4f\n", (float) q11, (float) q12, (float) q13, (float) q14);
    printf("%.4f, %.4f, %.4f, %.4f\n", (float) q21, (float) q22, (float) q23, (float) q24);
    printf("%.4f, %.4f, %.4f, %.4f\n", (float) q31, (float) q32, (float) q33, (float) q34);
    printf("%.4f, %.4f, %.4f, %.4f\n", (float) q41, (float) q42, (float) q43, (float) q44);
    printf("---------------\n");
    printf("%.4f, %.4f\n",(float) din,(float) done);


    LinearSolver(
	 a11, a12, a13, a14,
	 a21, a22, a23, a24,
	 a31, a32, a33, a34,
	 a41, a42, a43, a44,
	  b1,  b2,  b3,  b4,

	 x1, x2, x3, x4
    );
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << "------------- Solver Test -------------" << std::endl;
    printf("%.4f, %.4f, %.4f, %.4f\n", (float) x1, (float) x2, (float) x3, (float) x4);


    return 0;
}
