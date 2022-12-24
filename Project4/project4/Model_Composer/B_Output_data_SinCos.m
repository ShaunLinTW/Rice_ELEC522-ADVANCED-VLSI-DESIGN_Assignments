% Generate theta degree(-180~180) to radian(-3.14 ~ 3.14)
theta_array = (-pi+pi/180):1*pi/180:pi;

% Calculate true rotation for each angle
x_sw = cos(theta_array)*1 - sin(theta_array)*0;
y_sw = sin(theta_array)*1 + cos(theta_array)*0;

x_hw = out.x_out';
y_hw = out.y_out';

% Visualize the results
time = 1:4:(length(theta_array)); % 360 data are too dense to visualize, so here sampled to 90 data
figure()
plot(time, x_sw(1:4:(length(theta_array))),'LineWidth', 2, 'Color', '#0072BD');
hold on
plot(time, x_hw(28:4:(length(theta_array)+27)), '--o', 'Color', '#D95319');
hold off
legend('x Actual Value', 'x Cordic Value')
title('COS SIN mode - cos result visualize')
xlabel('Clock cycle')
ylabel('Y-vaule')

figure()
plot(time, y_sw(1:4:(length(theta_array))), 'LineWidth', 2, 'Color', '#0072BD');
hold on
plot(time, y_hw(28:4:(length(theta_array)+27)), '--o', 'Color', '#D95319');
hold off
legend('y Actual Value', 'y Cordic Value',...
    'Location', 'southeast')
title('COS SIN mode - sin result visualize')
xlabel('Clock cycle')
ylabel('Y-vaule')