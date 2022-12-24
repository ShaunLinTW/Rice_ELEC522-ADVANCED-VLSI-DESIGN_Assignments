#include <iostream>
#include "matmul.h"

using namespace std;

int main(int argc, char **argv)
{
   d_t in_mat_a[4][4] = {
      {3.2588,    2.5293,    3.8301,    3.8291},
      {3.6230,    0.3906,    3.8594,    1.9414},
      {0.5078,    1.1143,    0.6309,    3.2012},
      {3.6533,    2.1875,    3.8828,    0.5674}
   };
   d_t in_mat_b[4][4] = {
		    {1.6875,    2.6230,    2.7148,    2.6221},
		    {3.6631,    0.1426,    3.0312,    0.6846},
		    {3.1689,    3.3965,    2.9727,    2.8242},
		    {3.8379,    3.7363,    1.5693,    0.1270}
   };
   d_t hw_result[4][4], sw_result[4][4];
   d_t err_cnt = 0;

   // Generate the expected result
   // Iterate over the rows of the A matrix
   for(int i = 0; i < MAT_DIM; i++) {
      for(int j = 0; j < MAT_DIM; j++) {
         // Iterate over the columns of the B matrix
         sw_result[i][j] = 0;
         // Do the inner product of a row of A and col of B
         for(int k = 0; k < MAT_DIM; k++) {
            sw_result[i][j] += in_mat_a[i][k] * in_mat_b[k][j];
         }
      }
   }

#ifdef HW_COSIM
   // Run the AutoESL matrix multiply block
   m_t in_m_a;
   m_t in_m_b;
   for (int i = 0; i < 4; i++) {
	   for (int j = 0; j < 4; j++) {
		   in_m_a[i][j] = in_mat_a[i][j];
		   in_m_b[j][i] = in_mat_b[i][j];
	   }
   }
   hls::stream<v_t> inStreamA;
   hls::stream<v_t> inStreamB;
   hls::stream<d_t> outStream;
   for (int i = 0; i < 4; i++) {
	   for (int j = 0; j< 4; j++) {
		   inStreamA << in_m_a[i];
		   inStreamB << in_m_b[j];
	   }
   }
   cout << "**Debug: inStreamA Size - " << inStreamB.size() << endl;
   cout << "**Debug: inStreamB Size - " << inStreamB.size() << endl;
   for (int i = 0; i < 16; i++ ) VVM(inStreamA, inStreamB, outStream);
   cout << "**Debug: outStream Size - " << outStream.size() << endl;
   for (int i = 0; i < 4; i++) {
   	   for (int j = 0; j< 4; j++) {
   		outStream >> hw_result[i][j];
   	   }
   }
#endif

   // Print result matrix
   cout << "****************************** Software results. ******************************" << endl;
   cout << "{" << endl;
   //cout << setw(6);
   for (int i = 0; i < MAT_DIM; i++) {
      cout << "{";
      for (int j = 0; j < MAT_DIM; j++) {
         cout << sw_result[i][j];
         if (j == MAT_DIM - 1)
            cout << "}" << endl;
         else
            cout << ",";
      }
   }
   cout << "}" << endl;



#ifdef HW_COSIM
   // Print result matrix
   cout << "****************************** Hardware results. ******************************" << endl;

   cout << "{" << endl;
   //cout << setw(6);
   for (int i = 0; i < MAT_DIM; i++) {
      cout << "{";
      for (int j = 0; j < MAT_DIM; j++) {
         cout << hw_result[i][j];
         if (j == MAT_DIM - 1)
            cout << "}" << endl;
         else
            cout << ",";
      }
   }
   cout << "}" << endl;
#endif


#ifdef HW_COSIM
   // Print result matrix
   cout << "****************************** Diff results. **********************************" << endl;

   d_t err_tmp;
   cout << "{" << endl;
   //cout << setw(6);
   for (int i = 0; i < MAT_DIM; i++) {
      cout << "{";
      for (int j = 0; j < MAT_DIM; j++) {

         err_tmp = hw_result[i][j] - sw_result[i][j];
         if (err_tmp/sw_result < 0) err_cnt -= err_tmp/sw_result; else err_cnt += err_tmp/sw_result;
         cout << err_tmp;

         if (j == MAT_DIM - 1)
            cout << "}" << endl;
         else
            cout << ",";
      }
   }
   cout << "}" << endl;
#endif


#ifdef HW_COSIM
   cout << "****************************** Summary ****************************************" << endl;

   cout << "Report: " << err_cnt*100 << "% relative error detected!" << endl;
#endif
   return 0;
}

