#ifndef __CORDIC__
#define __CORDIC__

#include <stdint.h>
#include <ap_fixed.h>
#include <stdbool.h>

#define CORDIC_ANG_POINT 12
#define CORDIC_MAG_POINT 12

typedef  ap_fixed<16,4,AP_RND> CORDIC_MAG_TYPE;
typedef  ap_fixed<16,4,AP_RND> CORDIC_ANG_TYPE;

#define CORDIC_PI (CORDIC_ANG_TYPE)3.14159265358979

//#define CORDIC_MAG_TYPE __mag_type
//#define CORDIC_ANG_TYPE __ang_type

#define CORDIC_ITERATIONS	12
#define CORDIC_INV_K (CORDIC_MAG_TYPE) 0.607252935103139000000
 
#define CORDIC_SCALE_SHIFTS 7

//#define MODEL_COMPOSER

static CORDIC_ANG_TYPE Cordic_Rotations[CORDIC_ITERATIONS]=
{
		0.78539816339744800000,
		0.46364760900080600000,
		0.24497866312686400000,
		0.12435499454676100000,
		0.06241880999595740000,
		0.03123983343026830000,
		0.01562372862047680000,
		0.00781234106010111000,
		0.00390623013196697000,
		0.00195312251647882000,
		0.00097656218955931900,
		0.00048828121119489800/*,
		0.00024414062014936200,
		0.00012207031189367000,	//These iterations don't add any value to the computation, but were entered for completion purposes
		0.00006103515617420880,
		0.00003051757811552610/**/
};

static uint8_t CORDIC_SCALE_SHIFT[CORDIC_SCALE_SHIFTS] ={
		2,
		3,
		4,
		7,
		8,
		10,
		12/*,//
		14,
		16,
		19,
		20,
		22,
		23,
		24,
		25,
		31//*/
};

struct CORDIC_Cntl{
	uint8_t Inv_Tan:1;
	uint8_t Done:1;
};

void circular_cordic(
		CORDIC_ANG_TYPE angle_in,
		CORDIC_MAG_TYPE Inphase_In,
		CORDIC_MAG_TYPE Quadrature_In,
		CORDIC_ANG_TYPE *angle_Out,
		CORDIC_MAG_TYPE *Inphase_Out,
		CORDIC_MAG_TYPE *Quadrature_Out,
		bool arc_tan);
/*Circular cordic implementation for inverse tangent and/or cos(theta) sin(theta)*/

#endif
