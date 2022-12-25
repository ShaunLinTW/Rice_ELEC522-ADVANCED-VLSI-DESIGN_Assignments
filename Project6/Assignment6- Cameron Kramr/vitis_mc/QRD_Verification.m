clear %% Keep out the other junk

depth = 4;
iteration_interval = int16(18);
end_margin = int16(36);

unit_L = 17;

target_mat = [1, 0.5, 0.3333, 0.25;
             0.5, 0.3333, 0.25, 0.2;
             0.3333, 0.25, 0.2, 0.1667;
             0.25, 0.2, 0.1667, 0.1429];
%{
target_mat =[0.6900 0.5054 0.5914 0.5547;
        0.3784 0.2577 0.2073 0.6262;
        0.3401 0.8438 0.0687 0.4099;
        0.8799 0.3194 0.9805 0.0850];
  %}       

operations = int16(2*length(target_mat));

sim_length = double((depth + operations) * iteration_interval + end_margin);

ap_rst.signals.values = zeros(sim_length, 1);
ap_rst.time = 0:1:(sim_length - 1);
ap_rst.signals.dimensions = 1;
 
ap_start.signals.values = zeros(sim_length, 1);
ap_start.time = 0:1:(sim_length - 1);
ap_start.signals.dimensions = 1;
ap_start.signals.values(2) = 1;

in_11 = timeseries(target_mat(1,1));
in_12 = timeseries(target_mat(1,2));
in_13 = timeseries(target_mat(1,3));
in_14 = timeseries(target_mat(1,4));

in_21 = timeseries(target_mat(2,1));
in_22 = timeseries(target_mat(2,2));
in_23 = timeseries(target_mat(2,3));
in_24 = timeseries(target_mat(2,4));

in_31 = timeseries(target_mat(3,1));
in_32 = timeseries(target_mat(3,2));
in_33 = timeseries(target_mat(3,3));
in_34 = timeseries(target_mat(3,4));

in_41 = timeseries(target_mat(4,1));
in_42 = timeseries(target_mat(4,2));
in_43 = timeseries(target_mat(4,3));
in_44 = timeseries(target_mat(4,4));

%col_1 = timeseries(target_mat(1,:));
%col_2 = timeseries(target_mat(2,:));
%col_3 = timeseries(target_mat(3,:));
%col_4 = timeseries(target_mat(4,:));


start_new = timeseries(0);

sim_out = sim('Lab_Five_QRD');

R = [getdatasamples(sim_out.R_11, sim_length), getdatasamples(sim_out.R_12, sim_length), getdatasamples(sim_out.R_13, sim_length), getdatasamples(sim_out.R_14, sim_length);
    0, getdatasamples(sim_out.R_22, sim_length), getdatasamples(sim_out.R_23, sim_length), getdatasamples(sim_out.R_24, sim_length);
    0, 0, getdatasamples(sim_out.R_33, sim_length), getdatasamples(sim_out.R_34, sim_length);
    0, 0, 0, getdatasamples(sim_out.R_44, sim_length)
];

Q = [getdatasamples(sim_out.Q_11, sim_length), getdatasamples(sim_out.Q_12, sim_length), getdatasamples(sim_out.Q_13, sim_length), getdatasamples(sim_out.Q_14, sim_length);
    getdatasamples(sim_out.Q_21, sim_length), getdatasamples(sim_out.Q_22, sim_length), getdatasamples(sim_out.Q_23, sim_length), getdatasamples(sim_out.Q_24, sim_length);
    getdatasamples(sim_out.Q_31, sim_length), getdatasamples(sim_out.Q_32, sim_length), getdatasamples(sim_out.Q_33, sim_length), getdatasamples(sim_out.Q_34, sim_length);
    getdatasamples(sim_out.Q_41, sim_length), getdatasamples(sim_out.Q_42, sim_length), getdatasamples(sim_out.Q_43, sim_length), getdatasamples(sim_out.Q_44, sim_length)];

target_mat
Q
R
Product = Q'*R

compare = Product - target_mat

Q_self = Q'*Q

total_error = sum(sum(compare))



