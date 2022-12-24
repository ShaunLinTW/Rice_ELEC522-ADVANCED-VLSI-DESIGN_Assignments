thetas = [0 0.2617 0.5235 0.7853 1.047 1.308 1.57]
c_expected = cos(thetas)
cos_out = transpose(out.c_2var.DATA(25:31)) %cos_out 
er_cos = abs(c_s-out_c_2var)

s_s = sin(thetas)';
out_c_3var = out.c_3var.DATA(25:31).'; %sin_out
er_s = abs(s_s-out_c_3var)';

disp(out_c_2var)
disp((er_c))
disp(out_c_3var)
disp(er_s)



%out_c_7var = out.c_7var.DATA(24:35).';
%out_c_8var = out.c_8var.DATA(24:35).';
%disp(out_c_7var)
%disp(out_c_8var)