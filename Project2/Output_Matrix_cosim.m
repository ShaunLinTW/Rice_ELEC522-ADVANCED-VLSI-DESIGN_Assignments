% MATLAB developed at the Rice University. 
% Electrical and Computer Engineering Department. 
% Hsuan-You (Shaun) Lin (September 29, 2020)

% Program to show output data for 4x4 Matrix Multiplication cosim result.

C1_Matrix_var_cosim = out.C_Matrix_var_cosim.Data(8:11).';
C2_Matrix_var_cosim = out.C_Matrix_var_cosim.Data(25:28).';
C3_Matrix_var_cosim = out.C_Matrix_var_cosim.Data(42:45).';
C4_Matrix_var_cosim = out.C_Matrix_var_cosim.Data(59:62).';


C_Matrix_cosim = [C1_Matrix_var_cosim, C2_Matrix_var_cosim, C3_Matrix_var_cosim, C4_Matrix_var_cosim];
disp(flip(C_Matrix_cosim)')