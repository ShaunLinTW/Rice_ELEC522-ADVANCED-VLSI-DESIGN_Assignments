clear %% Keep out the other junk

iteration_interval = int16(18);
end_margin = int16(10);

input_mat = [2,1,3,1];
operations = int16(length(input_mat) + 1);

sim_length = double(operations * iteration_interval + end_margin);

tready.signals.values = zeros(sim_length, 1);
tready.time = 0:1:(sim_length - 1);
tready.signals.dimensions = 1;

tvalid.signals.values = zeros(sim_length, 1);
tvalid.time = 0:1:(sim_length - 1);
tvalid.signals.dimensions = 1;

tdata.signals.values = zeros(sim_length, 1);
tdata.time = 0:1:(sim_length - 1);
tdata.signals.dimensions = 1;

i = 0;
for value = input_mat
    tdata.signals.values((i * iteration_interval) + 1) = value;
    tvalid.signals.values((i * iteration_interval) + 1) = 1;
    
    i = i + 1;
end

sim_out = sim('fifo_test');