clear %% Keep out the other junk

iteration_interval = int16(18);
end_margin = int16(10);

input_mat = [1,1,1,1; 
             -pi/2, pi/2, pi/4, -pi/4];
operations = int16(length(input_mat));

sim_length = double(operations * iteration_interval + end_margin);

ap_rst.signals.values = zeros(sim_length, 1);
ap_rst.time = 0:1:(sim_length - 1);
ap_rst.signals.dimensions = 1;

ap_start.signals.values = zeros(sim_length, 1);
ap_start.time = 0:1:(sim_length - 1);
ap_start.signals.dimensions = 1;

sine_in.signals.values = zeros(sim_length, 1);
sine_in.time = 0:1:(sim_length - 1);
sine_in.signals.dimensions = 1;

angle_in.signals.values = zeros(sim_length, 1);
angle_in.time = 0:1:(sim_length - 1);
angle_in.signals.dimensions = 1;

i = 0;
for value = input_mat
    sine_in.signals.values((i * iteration_interval) + 1) = value(1);
    angle_in.signals.values((i * iteration_interval) + 1) = value(2);
    angle_in.signals.values((i * iteration_interval) + 2) = value(2);
    angle_in.signals.values((i * iteration_interval) + 3) = value(2);
    angle_in.signals.values((i * iteration_interval) + 4) = value(2);
    ap_start.signals.values((i * iteration_interval) + 1) = 1;
    
    i = i + 1;
end

sim_out = sim('rotate_verification_model');