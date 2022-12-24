b_matrix = [1 2 3 4;1 2 3 4;1 2 3 4;1 2 3 4];
b_matrixTranspose = b_matrix'; %Taking tranpose of second matrix since the columns are passed through

%b_signals = [b_matrixTranspose zeros(4,1)]
b_signals = b_matrixTranspose

%Creating individual structs to stream final, diagonalized matrix into the
%system generator input gateways
b1 = b_signals(1,:);
b1_var.time = 0:1:length(b_signals)-1;
b1_var.signals.values = b1';
b1_var.signals.dimensions = 1;

b2 = b_signals(2,:);
b2_var.time = 0:1:length(b_signals)-1;
b2_var.signals.values = b2';
b2_var.signals.dimensions = 1;

b3 = b_signals(3,:);
b3_var.time = 0:1:length(b_signals)-1;
b3_var.signals.values = b3';
b3_var.signals.dimensions = 1;

b4 = b_signals(4,:);
b4_var.time = 0:1:length(b_signals)-1;
b4_var.signals.values = b4';
b4_var.signals.dimensions = 1;
