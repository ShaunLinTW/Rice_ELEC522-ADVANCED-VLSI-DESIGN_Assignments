% Clears all variables previously assigned.
clear
% Closes all graphs and windows open.
close all

% Generate theta degree(-180~180) to radian(-3.14 ~ 3.14)
theta_array = (-pi+pi/180):1*pi/180:pi;

% Set the input data for cordic system
modes = timeseries(zeros(1, length(theta_array)));
x_in = timeseries(ones(1, length(theta_array)));
y_in = timeseries(zeros(1, length(theta_array)));
theta_in = timeseries(theta_array);
done = timeseries(zeros(1, length(theta_array)));