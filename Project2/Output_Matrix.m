% MATLAB developed at the Rice University. 
% Electrical and Computer Engineering Department. 
% Hsuan-You (Shaun) Lin (September 29, 2020)

% Program to show output data for 4x4 Matrix Multiplication result.

C1_Matrix_var = out.C_Matrix_var.Data(8:11).';
C2_Matrix_var = out.C_Matrix_var.Data(25:28).';
C3_Matrix_var = out.C_Matrix_var.Data(42:45).';
C4_Matrix_var = out.C_Matrix_var.Data(59:62).';

C_Matrix = [C1_Matrix_var, C2_Matrix_var, C3_Matrix_var, C4_Matrix_var];
disp(flip(C_Matrix)')