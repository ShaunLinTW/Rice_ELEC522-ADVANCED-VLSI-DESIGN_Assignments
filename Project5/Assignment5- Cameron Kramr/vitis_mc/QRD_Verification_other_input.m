clear %% Keep out the other junk

depth = 4;
iteration_interval = int16(18);
end_margin = int16(10);

unit_L = 17;

input_mat = [1, 0.5, 0.3333, 0.25;
             0.5, 0.3333, 0.25, 0.2;
             0.3333, 0.25, 0.2, 0.1667;
             0.25, 0.2, 0.1667, 0.1429;
             1, 0, 0, 0;
             0, 1, 0, 0;
             0, 0, 1, 0;
             0, 0, 0, 1];
operations = int16(length(input_mat));

sim_length = double((depth + operations) * iteration_interval + end_margin);

ap_rst.signals.values = zeros(sim_length, 1);
ap_rst.time = 0:1:(sim_length - 1);
ap_rst.signals.dimensions = 1;
 
ap_start = timeseries([ones(4,1);0]);

col_1 = timeseries(input_mat(1,:));
col_2 = timeseries(input_mat(2,:));
col_3 = timeseries(input_mat(3,:));
col_4 = timeseries(input_mat(4,:));

col_5.signals.values = zeros(sim_length, 1);
col_5.time = 0:1:(sim_length - 1);
col_5.signals.dimensions = 1;

col_6.signals.values = zeros(sim_length, 1);
col_6.time = 0:1:(sim_length - 1);
col_6.signals.dimensions = 1;

col_7.signals.values = zeros(sim_length, 1);
col_7.time = 0:1:(sim_length - 1);
col_7.signals.dimensions = 1;

col_8.signals.values = zeros(sim_length, 1);
col_8.time = 0:1:(sim_length - 1);
col_8.signals.dimensions = 1;

i = 0;
for value = input_mat
    col_5.signals.values((i * iteration_interval) + 1) = value(5);
    col_6.signals.values((i * iteration_interval) + 1) = value(6);
    col_7.signals.values((i * iteration_interval) + 1) = value(7);
    col_8.signals.values((i * iteration_interval) + 1) = value(8);
    
    i = i + 1;
end

