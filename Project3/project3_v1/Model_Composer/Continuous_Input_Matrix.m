% MATLAB developed at the Rice University. 
% Electrical and Computer Engineering Department. 
% Hsuan-You (Shaun) Lin (Oct. 20, 2022)

% Program to build random continuous input data for 4x4 Matrix Multiplication.

% Clears all variables previously assigned.
clear
% Closes all graphs and windows open.
close all

matrix_size = 4;

% Generating first set of random matrices to be inserted to HLS block 
a_1st = randi([1 10], matrix_size); 
b_1st = randi([1 10], matrix_size); 

a_2nd = randi([1 10], matrix_size); 
b_2nd = randi([1 10], matrix_size); 

a1_t = [zeros(4,1); a_1st(1,1); a_1st(2,1); a_1st(3,1); a_1st(4,1); zeros(1,1); a_2nd(1,1); a_2nd(2,1); a_2nd(3,1); a_2nd(4,1); zeros(15,1)]; 
a2_t = [zeros(4,1); a_1st(1,2); a_1st(2,2); a_1st(3,2); a_1st(4,2); zeros(1,1); a_2nd(1,2); a_2nd(2,2); a_2nd(3,2); a_2nd(4,2); zeros(15,1)]; 
a3_t = [zeros(4,1); a_1st(1,3); a_1st(2,3); a_1st(3,3); a_1st(4,3); zeros(1,1); a_2nd(1,3); a_2nd(2,3); a_2nd(3,3); a_2nd(4,3); zeros(15,1)]; 
a4_t = [zeros(4,1); a_1st(1,4); a_1st(2,4); a_1st(3,4); a_1st(4,4); zeros(1,1); a_2nd(1,4); a_2nd(2,4); a_2nd(3,4); a_2nd(4,4); zeros(15,1)];

b1_t = [b_1st(1,1); b_1st(1,2); b_1st(1,3); b_1st(1,4); b_2nd(1,1); b_2nd(1,2); b_2nd(1,3); b_2nd(1,4); zeros(15,1)]; 
b2_t = [b_1st(2,1); b_1st(2,2); b_1st(2,3); b_1st(2,4); b_2nd(2,1); b_2nd(2,2); b_2nd(2,3); b_2nd(2,4); zeros(15,1)]; 
b3_t = [b_1st(3,1); b_1st(3,2); b_1st(3,3); b_1st(3,4); b_2nd(3,1); b_2nd(3,2); b_2nd(3,3); b_2nd(3,4); zeros(15,1)];
b4_t = [b_1st(4,1); b_1st(4,2); b_1st(4,3); b_1st(4,4); b_2nd(4,1); b_2nd(4,2); b_2nd(4,3); b_2nd(4,4); zeros(15,1)]; 
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
disp("1st A Input Matrix:");
disp(a_1st);
disp("1st B Input Matrix:");
disp(b_1st);
result1 = a_1st * b_1st;
disp("1st A * B Matrix result:");
disp(result1);

disp("2nd A Input Matrix:");
disp(a_2nd);
disp("2nd B Input Matrix:");
disp(b_2nd);
result2 = a_2nd * b_2nd;
disp("2nd A * B Matrix result:");
disp(result2);