clear

sim_length = 5;

data_in = timeseries(1:3:25);
%tvalid = ones(1,length(data_in.Data));

tvalid.signals.values = ones(sim_length, 1);
tvalid.time = 0:1:(sim_length - 1);
tvalid.signals.dimensions = 1;

tvalid = ones(1,10);