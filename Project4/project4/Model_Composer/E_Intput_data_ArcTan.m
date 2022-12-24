% Clears all variables previously assigned.
clear
% Closes all graphs and windows open.
close all

% Generate theta degree(-180~180) to radian(-3.14 ~ 3.14)
theta_array = (-pi+pi/180):1*pi/180:pi;

% Generate vectors
x_vec = (cos(theta_array)*1 - sin(theta_array)*0);
y_vec = (sin(theta_array)*1 + cos(theta_array)*0);

% Set the input data for cordic system
modes = timeseries(ones(1, length(theta_array)));
x_in = timeseries(x_vec);
y_in = timeseries(y_vec);
theta_in = timeseries(zeros(1, length(theta_array)));
done = timeseries(zeros(1, length(theta_array)));