#include "cordic.h"

//perform the scale, dat_out = dat_in * 0.607...
VECTOR_TYPE scale(VECTOR_TYPE &dat_in)
{
	VECTOR_TYPE dat_out;
	dat_out = 	+	(dat_in)
				-	(dat_in >> 1)
				+	(dat_in >> 2)
				-	(dat_in >> 3)
				-	(dat_in >> 4)
				+	(dat_in >> 5)
				+	(dat_in >> 6)
				-	(dat_in >> 7)
				+	(dat_in >> 8)
				+	(dat_in >> 9)
				-	(dat_in >> 10)
				+	(dat_in >> 11)
				+	(dat_in >> 12);
//				+	(dat_in >> 13)
//				-	(dat_in >> 14)
//				+	(dat_in >> 15)
//				-	(dat_in >> 16)
//				-	(dat_in >> 17)
//				-	(dat_in >> 18)
//				-	(dat_in >> 19)
//				-	(dat_in >> 20)
//				-	(dat_in >> 21)
//				-	(dat_in >> 22)
//				-	(dat_in >> 23)
//				-	(dat_in >> 24)
//				-	(dat_in >> 25)
//				-	(dat_in >> 26)
//				-	(dat_in >> 27)
//				-	(dat_in >> 28)
//				-	(dat_in >> 29)
//				-	(dat_in >> 30)
//				-	(dat_in >> 31);

	return dat_out;
}

//perform the cordic algorithm
//mode 0: cos/sin mode, out_x = XcosT-YsinT, out_y = YcosT+XsinT
//mode 1: arctan mode,	out_x = modulo of a vector, out_y = arctan(T)
void cordic(THETA_TYPE theta_in, VECTOR_TYPE x_in, VECTOR_TYPE y_in, VECTOR_TYPE &out_x, VECTOR_TYPE &out_y, bool mode)
{
	#pragma HLS INTERFACE s_axilite port=return 	bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=theta_in 	bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=x_in		bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=y_in		bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=out_x		bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=out_y		bundle=HLS_CORDIC_PERIPH_BUS
	#pragma HLS INTERFACE s_axilite port=mode		bundle=HLS_CORDIC_PERIPH_BUS

	VECTOR_TYPE current_y;
	VECTOR_TYPE current_x;
	VECTOR_TYPE y_shift;
	VECTOR_TYPE x_shift;

	//mode 1: arctan mode
	if(mode == 1)
	{
		//let inputs to be positive
		if(x_in < 0)
		{
			current_x = -x_in;
		}
		else
		{
			current_x = x_in;
		}

		if(y_in < 0)
		{
			current_y = -y_in;
		}
		else
		{
			current_y = y_in;
		}

		//perform the iterations
		theta_in = 0;
		cordic_label0:for (int j = 0; j < NUM_ITERATIONS; j++)
		{
			y_shift = current_y >> j;
			x_shift = current_x >> j;

			if(current_y >= 0)
			{
				// Perform the rotation
				current_x = current_x + y_shift;
				current_y = current_y - x_shift;

				// Determine the new out_x
				theta_in = theta_in + cordic_phase[j];
			}
			else
			{
				// Perform the rotation
				current_x = current_x - y_shift;
				current_y = current_y + x_shift;

				// Determine the new out_x
				theta_in = theta_in - cordic_phase[j];
			}
		}
		out_x = scale(current_x);
		out_y = theta_in;

		//correct the angle to 0-360 degrees
		if(x_in < 0 && y_in >= 0)
		{
			out_y = (VECTOR_TYPE)HALF_RAD - theta_in;
		}
		else if(x_in <= 0 && y_in < 0)
		{
			out_y = (VECTOR_TYPE)HALF_RAD + theta_in;
		}
		else if(x_in > 0 && y_in < 0)
		{
			out_y = (VECTOR_TYPE)FULL_RAD - theta_in;
		}
		else
		{
			out_y = theta_in;
		}

	}
	//mode 0: cos/sin mode
	else if(mode == 0)
	{
		current_y = y_in;
		current_x = x_in;
		bool sine_sign = 1, cosine_sign = 1;
		//correct the angle to 0-360 degrees
		if(theta_in >= (VECTOR_TYPE)QUAR_RAD && theta_in < (VECTOR_TYPE)HALF_RAD)
		{
			theta_in = (VECTOR_TYPE)HALF_RAD - theta_in;
			sine_sign = 1;
			cosine_sign = 0;
		}
		else if(theta_in >= (VECTOR_TYPE)HALF_RAD && theta_in < (VECTOR_TYPE)THQU_RAD)
		{
			theta_in -= (VECTOR_TYPE)HALF_RAD;
			sine_sign = 0;
			cosine_sign = 0;
		}
		else if(theta_in >= (VECTOR_TYPE)THQU_RAD && theta_in < (VECTOR_TYPE)FULL_RAD + (VECTOR_TYPE)FRAC)
		{
			theta_in = (VECTOR_TYPE)FULL_RAD - theta_in;
			sine_sign = 0;
			cosine_sign = 1;
		}

		//perform the iterations
		cordic_label1:for (int j = 0; j < NUM_ITERATIONS; j++)
		{
			x_shift = current_x >> j;
			y_shift = current_y >> j;

			if(theta_in >= 0)
			{
				// Perform the rotation
				current_x = current_x - y_shift;
				current_y = current_y + x_shift;

				// Determine the new theta_in
				theta_in = theta_in - cordic_phase[j];
			}
			else
			{
				// Perform the rotation
				current_x = current_x + y_shift;
				current_y = current_y - x_shift;

				// Determine the new theta_in
				theta_in = theta_in + cordic_phase[j];
			}
		}
		out_x = scale(current_x);
		out_y = scale(current_y);

		//determine whether the sign is positive or negative
		if(cosine_sign == 0)
		{
			out_x = -out_x;
		}
		if(sine_sign == 0)
		{
			out_y = -out_y;
		}
	}
}
