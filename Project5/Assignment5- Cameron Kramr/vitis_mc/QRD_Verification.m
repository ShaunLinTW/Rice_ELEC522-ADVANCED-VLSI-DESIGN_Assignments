clear %% Keep out the other junk

depth = 4;
iteration_interval = int16(18);
end_margin = int16(36);

unit_L = 17;

target_mat = [1, 0.5, 0.3333, 0.25, zeros(1,10), 1, 0.5, 0.3333, 0.25;
             0.5, 0.3333, 0.25, 0.2, zeros(1,10), 0.5, 0.3333, 0.25, 0.2;
             0.3333, 0.25, 0.2, 0.1667, zeros(1,10), 0.3333, 0.25, 0.2, 0.1667;
             0.25, 0.2, 0.1667, 0.1429, zeros(1,10), 0.25, 0.2, 0.1667, 0.1429];

target_mat =[0.6900 0.5054 0.5914 0.5547;
        0.3784 0.2577 0.2073 0.6262;
        0.3401 0.8438 0.0687 0.4099;
        0.8799 0.3194 0.9805 0.0850];
         
         
operations = int16(2*length(target_mat));

sim_length = double((depth + operations) * iteration_interval + end_margin);

ap_rst.signals.values = zeros(sim_length, 1);
ap_rst.time = 0:1:(sim_length - 1);
ap_rst.signals.dimensions = 1;
 
ap_start.signals.values = zeros(sim_length, 1);
ap_start.time = 0:1:(sim_length - 1);
ap_start.signals.dimensions = 1;
ap_start.signals.values(2) = 1;

col_1 = timeseries(target_mat(1,:));
col_2 = timeseries(target_mat(2,:));
col_3 = timeseries(target_mat(3,:));
col_4 = timeseries(target_mat(4,:));


out_start = 239;
extraction_width = 8;
read_sig = timeseries([0,0,ones(1,extraction_width)], [0,out_start,(out_start):1:out_start + extraction_width - 1]);

write_sig = timeseries([1,1,1,1]);

sim_out = sim('Lab_Five_QRD');

row_1 = getdatasamples(sim_out.row_1, (out_start + 2):(out_start + extraction_width + 2))';
row_2 = [0, getdatasamples(sim_out.row_2, (out_start + 2):(out_start + extraction_width + 1))'];
row_3 = [0, 0, getdatasamples(sim_out.row_3, (out_start + 2):(out_start + extraction_width))'];
row_4 = [0, 0, 0, getdatasamples(sim_out.row_4, (out_start + 2):(out_start + extraction_width - 1))'];

output = [row_1; row_2; row_3; row_4];
R = output(:,1:4);
Q = output(:,5:8);

Product = R*Q;

compare = Product - target_mat

total_error = sum(sum(compare))

