% Generate theta degree(-180~180) to radian(-3.14 ~ 3.14)
theta_array = (-pi+pi/180):1*pi/180:pi;

% Generate vectors
x_vec = (cos(theta_array)*1 - sin(theta_array)*0);
y_vec = (sin(theta_array)*1 + cos(theta_array)*0);

len_hw = out.x_out';
theta_hw = out.theta_out';

len_sw = sqrt(x_vec.^2+y_vec.^2);
theta_sw = atan2(y_vec, x_vec);

len_cosim = out.x_out_cosim';
theta_cosim = out.theta_out_cosim';

% Visualize the results
time = 1:4:(length(theta_array)); % 360 data are too dense to visualize, so here sampled to 90 data
figure()
hold on
plot(time, len_sw(1:4:(length(theta_array))), 'LineWidth', 8, 'Color', '#0072BD');
plot(time, len_hw(28:4:(length(theta_array)+27)), '--o', 'Color', '#D95319');
plot(time, len_cosim(28:4:(length(theta_array)+27)), '*', 'Color', '#EDB120');
hold off
legend('length Actual Value', 'length Cordic Value', 'length Cordic Co-sim Value')
title('ARCTAN mode - length result visualize')
xlabel('Clock cycle')
ylabel('Y-vaule')
xlim([0 400])
ylim([0 2])

figure()
hold on
plot(time, theta_sw(1:4:(length(theta_array))), 'LineWidth', 8, 'Color', '#0072BD');
plot(time, theta_hw(28:4:(length(theta_array)+27)), '--o', 'Color', '#D95319');
plot(time, theta_cosim(28:4:(length(theta_array)+27)), '*', 'Color', '#EDB120');
hold off
legend('theta Actual Value', 'theta Cordic Value', 'theta Cordic Co-sim Value',...
    'Location', 'northwest')
title('ARCTAN mode - theta result visualize')
xlabel('Clock cycle')
ylabel('Y-vaule')