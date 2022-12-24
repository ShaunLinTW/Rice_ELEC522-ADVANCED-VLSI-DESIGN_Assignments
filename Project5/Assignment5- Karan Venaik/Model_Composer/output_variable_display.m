out_arctan_var = out.arctan_var.DATA(1:100).';
out_c_var = out.c_var.DATA(1:100).';
out_register_var = out.register_var.DATA(1:100).';
out_ap_done_var = out.ap_done_var.DATA(1:100).'

strippedArctanVar = [];
strippedCVar = [];
strippedRegisterVar = [];
for i = 1:length(out_arctan_var)
    if ~(isnan(out_arctan_var(i)))
        strippedArctanVar = [strippedArctanVar,(out_arctan_var(i))];
    end
end
strippedArctanVar
% 
% for i = 1:length(out_c_var)
%     if ~(isnan(out_c_var(i)))
%         strippedCVar = [strippedCVar,(out_c_var(i))];
%     end
% end
% strippedCVar

for i = 1:length(out_register_var)
    if ~(isnan(out_register_var(i)))
        strippedRegisterVar = [strippedRegisterVar,(out_register_var(i))];
    end
end
strippedRegisterVar


%out_c3_var = out.c3_var.DATA(1:13).';
%out_c4_var = out.c4_var.DATA(1:13).';
%out_c_var = cat(1, out_c1_var, out_c2_var, out_c3_var, out_c4_var)

% out_c1_var_cosim = out.c1_var_cosim.DATA(1:13).';
% out_c2_var_cosim = out.c2_var_cosim.DATA(1:13).';
% out_c3_var_cosim = out.c3_var_cosim.DATA(1:13).';
% out_c4_var_cosim = out.c4_var_cosim.DATA(1:13).';
% out_c_var = cat(1, out_c1_var_cosim, out_c2_var_cosim, out_c3_var_cosim, out_c4_var_cosim)