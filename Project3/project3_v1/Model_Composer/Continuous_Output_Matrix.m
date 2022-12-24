% MATLAB developed at the Rice University. 
% Electrical and Computer Engineering Department. 
% Hsuan-You (Shaun) Lin (Oct. 20, 2022)

% Program to show continuous output data for 4x4 Matrix Multiplication.

matrix_size = 4;
number_of_matrix = 2;

for count = 0:(number_of_matrix - 1)
    arr = getdatasamples(out.res,[((matrix_size)^2-3) + 5 * count : (matrix_size)^2 + 5 * count]);
    c=dec2hex(arr, matrix_size^2);

    c11 =hex2dec(c(1, 13:16));
    c12 =hex2dec(c(1, 9:12));
    c13 =hex2dec(c(1, 5:8));
    c14 =hex2dec(c(1, 1:4));
    c21 =hex2dec(c(2, 13:16));
    c22 =hex2dec(c(2, 9:12));
    c23 =hex2dec(c(2, 5:8));
    c24 =hex2dec(c(2, 1:4));
    c31 =hex2dec(c(3, 13:16));
    c32 =hex2dec(c(3, 9:12));
    c33 =hex2dec(c(3, 5:8));
    c34 =hex2dec(c(3, 1:4));
    c41 =hex2dec(c(4, 13:16));
    c42 =hex2dec(c(4, 9:12));
    c43 =hex2dec(c(4, 5:8));
    c44 =hex2dec(c(4, 1:4));

    result_after_sim = [c11, c12, c13, c14;
                        c21, c22, c23, c24;
                        c31, c32, c33, c34;
                        c41, c42, c43, c44];
    disp("Continuous matrix result after simulation:");
    disp(result_after_sim);
end