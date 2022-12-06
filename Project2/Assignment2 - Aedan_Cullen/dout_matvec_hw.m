function result = dout_matvec_hw(n, out)
    result = zeros(4, n);
    for t = 0:n - 1
        result(1, t + 1) = out.row1_out_hw.DATA(10 + 4*t);
        result(2, t + 1) = out.row2_out_hw.DATA(10 + 4*t);
        result(3, t + 1) = out.row3_out_hw.DATA(10 + 4*t);
        result(4, t + 1) = out.row4_out_hw.DATA(10 + 4*t);
    end
end
