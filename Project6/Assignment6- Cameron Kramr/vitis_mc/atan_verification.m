clear %% Keep out the other junk

iteration_interval = int16(18);
end_margin = int16(20);

input_mat = [1, 0.5, 0.3333, 0.25,zeros(1,80),1, 0.5, 0.3333, 0.25,];
operations = int16(length(input_mat));

sim_length = double(operations * iteration_interval + end_margin);

ap_rst.signals.values = zeros(sim_length, 1);
ap_rst.time = 0:1:(sim_length - 1);
ap_rst.signals.dimensions = 1;

ap_start = timeseries([ones(4,1); zeros(80,1); ones(4,1)]);
sine_in = timeseries(input_mat);

i = 0;
for value = input_mat
    %sine_in.signals.values((i * iteration_interval) + 1) = value;
    %ap_start.signals.values((i * iteration_interval) + 1) = 1;
    
    i = i + 1;
end

sim_out = sim('atan_verification_model');