out_c1_var = out.c1_var.DATA(1:13).';
out_c2_var = out.c2_var.DATA(1:13).';
out_c3_var = out.c3_var.DATA(1:13).';
out_c4_var = out.c4_var.DATA(1:13).';
out_c_var = cat(1, out_c1_var, out_c2_var, out_c3_var, out_c4_var)

out_c1_var_cosim = out.c1_var_cosim.DATA(1:13).';
out_c2_var_cosim = out.c2_var_cosim.DATA(1:13).';
out_c3_var_cosim = out.c3_var_cosim.DATA(1:13).';
out_c4_var_cosim = out.c4_var_cosim.DATA(1:13).';
out_c_var = cat(1, out_c1_var_cosim, out_c2_var_cosim, out_c3_var_cosim, out_c4_var_cosim)