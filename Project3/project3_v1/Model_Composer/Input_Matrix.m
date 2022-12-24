% MATLAB developed at the Rice University. 
% Electrical and Computer Engineering Department. 
% Hsuan-You (Shaun) Lin (Oct. 20, 2022)

% Program to build random input data for 4x4 Matrix Multiplication.

% Clears all variables previously assigned.
clear
% Closes all graphs and windows open.
close all

matrix_size = 4;

% Generating first set of random matrices to be inserted to HLS block 
a = randi([1 10], matrix_size);
b = randi([1 10], matrix_size);
a1_t = [zeros(4,1); a(1,1); a(2,1); a(3,1); a(4,1); zeros(9,1)]; 
a2_t = [zeros(4,1); a(1,2); a(2,2); a(3,2); a(4,2); zeros(9,1)]; 
a3_t = [zeros(4,1); a(1,3); a(2,3); a(3,3); a(4,3); zeros(9,1)]; 
a4_t = [zeros(4,1); a(1,4); a(2,4); a(3,4); a(4,4); zeros(9,1)]; 

b1_t = [b(1,1); b(1,2); b(1,3); b(1,4); zeros(18,1)]; 
b2_t = [b(2,1); b(2,2); b(2,3); b(2,4); zeros(18,1)]; 
b3_t = [b(3,1); b(3,2); b(3,3); b(3,4); zeros(18,1)]; 
b4_t = [b(4,1); b(4,2); b(4,3); b(4,4); zeros(18,1)]; 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Constructing the inputs to be inserted to the HLS block 
a1 = timeseries(a1_t); 
a2 = timeseries(a2_t); 
a3 = timeseries(a3_t); 
a4 = timeseries(a4_t); 
b1 = timeseries(b1_t); 
b2 = timeseries(b2_t); 
b3 = timeseries(b3_t); 
b4 = timeseries(b4_t); 
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp("A Input Matrix:");
disp(a);
disp("B Input Matrix:");
disp(b);
result = a * b;
disp("A*B Matrix result:");
disp(result);