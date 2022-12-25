x1_col = downsample(out.out_x_col(634:800),42);
x2_col = downsample(out.out_x_col(849:end),42);

x1 = [x1_col(4)'; x1_col(3)'; x1_col(2)'; x1_col(1)'];
disp('x1');
disp(x1);

x2 = [x2_col(4)'; x2_col(3)'; x2_col(2)'; x2_col(1)'];
disp('x2');
disp(x2);