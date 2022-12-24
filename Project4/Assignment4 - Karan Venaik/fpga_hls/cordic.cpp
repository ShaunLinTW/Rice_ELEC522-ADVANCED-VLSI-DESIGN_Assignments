#include "cordic.h"
#include <iostream>

using namespace std;

//Function Name: cordic() - CORDIC block that calculates the sine/cosine of an input angle (rotation mode) or the magnitude/arctangent of an input vector (vector mode)
//bool cordicMode: Selects between "Rotation Mode" (false/0/low), or "Vector Mode" (true/1/high)
//
//THETA_TYPE targetAnglePhi:
//(i) "Rotation Mode" - The angle (radian) who's sine and cosine the CORDIC module calculates.
//(ii) "Vector Mode" - Unused (must be set to 0 (zero)).
//
//COS_SIN_TYPE xCartesian:
//(i) "Rotation Mode" - The length of unit vector as aligned with X-axis or the Cartesian X-coordinate (must be set to 1 (one)).
//(ii) "Vector Mode" - Cartesian X-coordinate to calculate arctan(y/x) and sqrt(x^2 + y^2).
//
//COS_SIN_TYPE yCartesian:
//(i) "Rotation Mode" - The length of unit vector as aligned with Y-axis or the Cartesian Y-coordinate (must be set to 0 (zero)).
//(ii) "Vector Mode" - Cartesian Y-coordinate to calculate arctan(y/x) and sqrt(x^2 + y^2).
//
//COS_SIN_TYPE &arctan:
//(i) "Rotation Mode" - Unused (Junk/Can be ignored).
//(ii) "Vector Mode" - Value of calculated arctan(y/x) as available to the test function.
//
//COS_SIN_TYPE &s:
//(i) "Rotation Mode" - Value of calculated sine(targetAnglePhi) as available to the test function.
//(ii) "Vector Mode" - Unused (Junk/Can be ignored).
//
//COS_SIN_TYPE &c:
//(i) "Rotation Mode" - Value of calculated cosine(targetAnglePhi) as available to the test function.
//(ii) "Vector Mode" - Value of calculated sqrt(x^2 + y^2) as available to the test function.

void cordic(bool cordicMode, THETA_TYPE targetAnglePhi, COS_SIN_TYPE xCartesian, COS_SIN_TYPE yCartesian, COS_SIN_TYPE &arctan, COS_SIN_TYPE &s, COS_SIN_TYPE &c)
{
//#pragma HLS INTERFACE mode=s_axilite port=return
//#pragma HLS INTERFACE mode=s_axilite port=c
//#pragma HLS INTERFACE mode=s_axilite port=s
//#pragma HLS INTERFACE mode=s_axilite port=arctan
//#pragma HLS INTERFACE mode=s_axilite port=yCartesian
//#pragma HLS INTERFACE mode=s_axilite port=xCartesian
//#pragma HLS INTERFACE mode=s_axilite port=targetAnglePhi
//#pragma HLS INTERFACE mode=s_axilite port=cordicMode

	//In "Rotation Mode", there are three angles, namely
	//(i) Phi - The target angle for which we must calculate sine and cosine. We want to reach/"binary search" for this angle iteratively through successively smaller rotations
	//(ii) Alpha - The angle by which we are rotating every iteration. Angle for a given iteration "i" can be computed by arctan(2^-i).
	//(iii) Theta - The cumulativeAngle we have obtained using iterative rotations. We aim to make this equivalent/very close to the target angle Phi.
  THETA_TYPE cumulativeAngleTheta = 0;
  THETA_TYPE currentRotationAngleAlpha = 0;

  //Minimization function allows us to direct the rotation for each iteration. We can change minimization function as necessary.
  // "Rotation Mode" - Difference between cumulativeAngleTheta and the targetAnglePhi (How far away are we from the angle we need to be at?)
  // "Vector Mode" - The Y component of vector to be rotated/Cartesian Y-coordinate
  THETA_TYPE minimizationFunction = 0;
  if(!cordicMode)
  {
	  minimizationFunction = cumulativeAngleTheta - targetAnglePhi;
  }
  else
  {
	  minimizationFunction = yCartesian;
  }

  //Total number of iterations conducted to reach convergence
  int totalIterations = 20;

#pragma HLS PIPELINE II = 1
  //Starting rotation iteration process
  for (int currentIteration = 0; currentIteration < totalIterations; currentIteration++)
  {
	  //Right Shifting the cartesian X- and Y-coordinates to provide efficient rotation instead of multiplication
      COS_SIN_TYPE cos_shift = xCartesian >> currentIteration;
      COS_SIN_TYPE sin_shift = yCartesian >> currentIteration;

      //Extract the rotation angle corresponding to the iteration from the precomputed/provided lookup table
      currentRotationAngleAlpha = rotationAngles[currentIteration];

      //Which way do we rotate?
      //If the minimizationFunction is -ve,
      //(i) "Rotation Mode" - Counterclockwise
      //(ii) "Vector Mode" - Clockwise
    if(minimizationFunction < 0)
    {
        xCartesian = xCartesian - sin_shift;
        yCartesian = yCartesian + cos_shift;
        if (!cordicMode)
		{
		//Update cumulativeAngleTheta that has been covered/rotated through
        //Update Minimization function since we are getting closer
        cumulativeAngleTheta = cumulativeAngleTheta + currentRotationAngleAlpha;
		minimizationFunction = cumulativeAngleTheta - targetAnglePhi;
		}
		else if (cordicMode)
		{
		//Update minimizationFunction
		cumulativeAngleTheta = cumulativeAngleTheta - currentRotationAngleAlpha;
		minimizationFunction = yCartesian;
		}
    }

    //Which way do we rotate?
    //If the minimizationFunction is +ve,
    //(i) "Rotation Mode" - Clockwise
    //(ii) "Vector Mode" - Counterclockwise
    else
    {
        xCartesian = xCartesian + sin_shift;
        yCartesian = yCartesian - cos_shift;
		if (!cordicMode)
		{
		//Do SinCos
		cumulativeAngleTheta = cumulativeAngleTheta - currentRotationAngleAlpha;
		minimizationFunction = cumulativeAngleTheta - targetAnglePhi;
		}
		else if (cordicMode)
		{
		//Do arctan
		cumulativeAngleTheta = cumulativeAngleTheta + currentRotationAngleAlpha;
		minimizationFunction = yCartesian;
		}
    }
  }

  //Scaling Factor correction implementation as covered in lecture on 11/10
  //Manually unrolled to ensure pipelining
  COS_SIN_TYPE xCartesianTemp = xCartesian;
  COS_SIN_TYPE yCartesianTemp = yCartesian;
  xCartesianTemp = xCartesian - (xCartesian >> 1);
  yCartesianTemp = yCartesian - (yCartesian >> 1);
  xCartesian = xCartesianTemp;
  yCartesian = yCartesianTemp;
  xCartesianTemp = xCartesian + (xCartesian >> 2);
  yCartesianTemp = yCartesian + (yCartesian >> 2);
  xCartesian = xCartesianTemp;
  yCartesian = yCartesianTemp;
  xCartesianTemp = xCartesian - (xCartesian >> 5);
  yCartesianTemp = yCartesian - (yCartesian >> 5);
  xCartesian = xCartesianTemp;
  yCartesian = yCartesianTemp;
  xCartesianTemp = xCartesian + (xCartesian >> 10);
  yCartesianTemp = yCartesian + (yCartesian >> 10);
  xCartesian = xCartesianTemp;
  yCartesian = yCartesianTemp;
  xCartesianTemp = xCartesian + (xCartesian >> 16);
  yCartesianTemp = yCartesian + (yCartesian >> 16);
  xCartesian = xCartesianTemp;
  yCartesian = yCartesianTemp;
  xCartesianTemp = xCartesian + (xCartesian >> 19);
  yCartesianTemp = yCartesian + (yCartesian >> 19);
  xCartesian = xCartesianTemp;
  yCartesian = yCartesianTemp;
  xCartesianTemp = xCartesian + (xCartesian >> 22);
  yCartesianTemp = yCartesian + (yCartesian >> 22);
  xCartesian = xCartesianTemp;
  yCartesian = yCartesianTemp;

  s = yCartesian;
  c = xCartesian;
  arctan = cumulativeAngleTheta;
}
