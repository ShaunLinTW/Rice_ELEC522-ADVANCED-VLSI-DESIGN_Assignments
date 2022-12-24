%out_c_1var = out.c_1var.DATA(25:32).'; %t_out
theta_vals = [0 0.2617 0.5235 0.7853 1.047 1.308 1.57]
cos_hls_out = transpose(out.c_2var.DATA(25:32)) %cos_out 
sin_hls_out = transpose(out.c_3var.DATA(25:32)) %sin_out

x_cordic = transpose(out.c_4var.DATA(25:32)) %x_cordic
y_cordic = transpose(out.c_5var.DATA(25:32)) %y_cordic

diff_x = abs(x_cordic - cos_hls_out)
diff_y = abs(y_cordic - sin_hls_out) 
%out_c_6var = transpose(out.c_6var.DATA(25:32)) %t_cordic
%disp(out_c_4var)
%disp(out_c_5var)
%disp(out_c_6var)


%out_c_7var = out.c_7var.DATA(24:35).';
%out_c_8var = out.c_8var.DATA(24:35).';
%disp(out_c_7var)
%disp(out_c_8var)