clc;
%sin
%Output - Designed CORDIC Module
out_designed_s_var = out.designed_s_var.DATA(15:testVectorLength-5).' 
out_HWCOSIMdesigned_s_var = out.HWCOSIMdesigned_s_var.DATA(15:testVectorLength-5).' 
%Output - Xilinx In-Built CORDIC Module
out_Xilinx_s_var = out.Xilinx_s_var.DATA(27:26+length(out_designed_s_var)).' 
%MATLAB Generated Sin
matlabSinFull = sin(angleRadiansSignals);
matlabSin = matlabSinFull(1:length(out_designed_s_var))
%Error Difference b/w Designed Arctan Module and Arctan generated using
errorSinCORDICMATLAB = (out_designed_s_var-matlabSin)
%Error Differennce b/w Designed Arctan Module and XILINX CORDIC Module
errorSinCORDICXILINX = (out_designed_s_var-out_Xilinx_s_var)

%cos
%Output - Designed CORDIC Module
out_designed_c_var = out.designed_c_var.DATA(15:testVectorLength-5).' 
out_HWCOSIMdesigned_c_var = out.HWCOSIMdesigned_c_var.DATA(15:testVectorLength-5).' 
%Output - Xilinx In-Built CORDIC Module
out_Xilinx_c_var = out.Xilinx_c_var.DATA(27:26+length(out_designed_c_var)).' 
%MATLAB Generated Sin
matlabCosFull = cos(angleRadiansSignals);
matlabCos = matlabCosFull(1:length(out_designed_c_var))
%Error Difference b/w Designed Arctan Module and Arctan generated using
errorCosCORDICMATLAB = (out_designed_c_var-matlabCos)
%Error Differennce b/w Designed Arctan Module and XILINX CORDIC Module
errorCosCORDICXILINX = (out_designed_c_var-out_Xilinx_c_var)