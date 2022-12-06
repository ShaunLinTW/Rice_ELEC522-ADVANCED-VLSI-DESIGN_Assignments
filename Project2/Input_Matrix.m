% MATLAB developed at the Rice University. 
% Electrical and Computer Engineering Department. 
% Hsuan-You (Shaun) Lin (September 29, 2020)

% Program to build input data for 4x4 Matrix Multiplication.

% Clears all variables previously assigned.
clear
% Closes all graphs and windows open.
close all

% 4x4 Matrix use value 4 for signals.values
Cycle.time = [0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15];
Cycle.signals.values = [ 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4]';
Cycle.signals.dimensions = 1;

% A 4x4 Matrix
A_Input_ori = [5 2 3 1;
               1 3 2 4;
               6 7 9 3;
               3 5 2 4];
% Matrix A need to transpose, because the input will be in column
A_Input = A_Input_ori';

%------------------------------------------%
% B 4x4 Matrix
B_Input = [1 1 1 1;
           1 1 1 1;
           1 1 1 1;
           1 1 1 1];
disp(A_Input_ori)
disp(B_Input)
disp(A_Input_ori*B_Input)