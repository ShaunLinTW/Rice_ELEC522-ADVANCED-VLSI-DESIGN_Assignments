clc;
a_matrix = [1 2 3 4; 1 2 3 4 ; 1 2 3 4; 1 2 3 4];
a_matrixTranspose = a_matrix; %Do not tranpose first matrix since the rows are passed through

%a_signals = [a_matrix zeros(4,1)]
a_signals = a_matrix

a1 = a_signals(1,:);
a1_var.time = 0:1:length(a_signals)-1;
a1_var.signals.values = a1';
a1_var.signals.dimensions = 1;

a2 = a_signals(2,:);
a2_var.time = 0:1:length(a_signals)-1;
a2_var.signals.values = a2';
a2_var.signals.dimensions = 1;

a3 = a_signals(3,:);
a3_var.time = 0:1:length(a_signals)-1;
a3_var.signals.values = a3';
a3_var.signals.dimensions = 1;

a4 = a_signals(4,:);
a4_var.time = 0:1:length(a_signals)-1;
a4_var.signals.values = a4';
a4_var.signals.dimensions = 1;
