clc

%Output - Designed CORDIC Module
out_designed_arctan_var = out.designed_arctan_var.DATA(15:testVectorLength-5).' %arctan(y/x) in radians
out_HWCOSIMdesigned_arctan_var = out.HWCOSIMdesigned_arctan_var.DATA(15:testVectorLength-5).'
%Output - Xilinx In-Built CORDIC Module
out_Xilinx_arctan_var = out.Xilinx_arctan_var.DATA(21:20+length(out_designed_arctan_var)).' %arctan(y/x) in radians
%MATLAB Generated Arctan
matlabArctanFull = (atan(yCartesianSignal./xCartesianSignal));
matlabArctan = matlabArctanFull(1:length(out_designed_arctan_var))

%Error Differennce b/w Designed Arctan Module and Arctan generated using
percentageErrorArctanCORDICMATLAB = (out_designed_arctan_var-matlabArctan)%./matlabArctan)*100
%averagePercentageErrorArctanCORDICMATLAB = mean(percentageErrorArctanCORDICMATLAB);

%Error Differennce b/w Designed Arctan Module and XILINX CORDIC Module
percentageErrorArctanCORDICXILINX = (out_designed_arctan_var-out_Xilinx_arctan_var)%./out_Xilinx_arctan_var)*100
%averagePercentageErrorArctanCORDICXILINX = mean(percentageErrorArctanCORDICXILINX);
