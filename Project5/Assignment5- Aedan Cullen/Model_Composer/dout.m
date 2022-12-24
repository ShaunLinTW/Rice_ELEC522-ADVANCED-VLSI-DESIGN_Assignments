function result = dout(n, out)

    ival = 20;

    result = zeros(4, 8*n);
    size_result = size(result);
    
    for t = 0:size_result(2) - 1
        result(1, t + 1) = out.row1_out.DATA(ival*8 + ival*t);
        result(2, t + 1) = out.row2_out.DATA(ival*8 + ival*t);
        result(3, t + 1) = out.row3_out.DATA(ival*8 + ival*t);
        result(4, t + 1) = out.row4_out.DATA(ival*8 + ival*t);
    end
end
