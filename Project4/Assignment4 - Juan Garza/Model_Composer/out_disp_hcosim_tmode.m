
tan_input_hcs = [0 0.2679 0.5774 1 1.7320 3.7322]

arctan_vals = transpose(out.c_1var.DATA(25:30)) %t_out
expected_vals_thcm = transpose(transpose(atan(t_var_ratio)))
errror_hctan = (arctan_vals-atan(t_var_ratio))*100

%disp(transpose(atan(t_var_ratio))) % values expected
%disp(transpose(er(6,:)*100))%error from tan
%displays errors as matrix


%out_c_7var = out.c_7var.DATA(24:35).';
%out_c_8var = out.c_8var.DATA(24:35).';
%disp(out_c_7var)
%disp(out_c_8var)