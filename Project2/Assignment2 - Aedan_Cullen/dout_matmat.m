function result = dout_matmat(n, out)
    result = zeros(4, 4*n);
    result(1, 1:end) = out.row1_out.DATA(10:10 + 4*n - 1);
    result(2, 1:end) = out.row2_out.DATA(10:10 + 4*n - 1);
    result(3, 1:end) = out.row3_out.DATA(10:10 + 4*n - 1);
    result(4, 1:end) = out.row4_out.DATA(10:10 + 4*n - 1);
end
