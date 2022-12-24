
%% Load data into workspace - one matrix

is_two = 0;

start_array = [1, zeros(1,599)];    % New matrix pulse
start = timeseries(start_array);

A = [0.69 0.5054 0.5914 0.5547;     % Matrix
     0.3784 0.2577 0.2073 0.6262; 
     0.3401 0.8438 0.0687 0.4099; 
     0.8799 0.3194 0.9805 0.0850];

% A = [0.8 0.7 0.6 0.5;
%      0.7 0.6 0.5 0.4;
%      0.6 0.5 0.4 0.3;
%      0.5 0.4 0.3 0.2];

col1 = [kron(A(:,1)',ones(1,27)), zeros(1, 200)];    % Reverse column, upsample & hold vals
col2 = [zeros(1,27),kron(A(:,2)',ones(1,27)), zeros(1, 200)]; 
col3 = [zeros(1,54),kron(A(:,3)',ones(1,27)), zeros(1, 200)]; 
col4 = [zeros(1,81),kron(A(:,4)',ones(1,27)), zeros(1, 200)];

Acol1 = timeseries(col1); Acol2 = timeseries(col2);     % Convert to timeseries
Acol3 = timeseries(col3); Acol4 = timeseries(col4);

I = [1 0 0 0; 
     0 1 0 0; 
     0 0 1 0; 
     0 0 0 1];   % Identity matrix

test = fliplr(I(:,1)');
Icol1 = [zeros(1,108),kron(I(:,1)',ones(1,27))];
Icol2 = [zeros(1,135),kron(I(:,2)',ones(1,27))];
Icol3 = [zeros(1,162),kron(I(:,3)',ones(1,27))];
Icol4 = [zeros(1,189),kron(I(:,4)',ones(1,27))];
Icol1_t = timeseries(Icol1);
Icol2_t = timeseries(Icol2);
Icol3_t = timeseries(Icol3);
Icol4_t = timeseries(Icol4);

ctrl = [zeros(1, 108), 1, zeros(1, 200)];
ctrl_t = timeseries(ctrl);
%% load data into workspace - 2*2 matrix

% A = [0.7 0.6;
%      0.5 0.4];
% 
% AtestCol1 = [kron(fliplr(A(:,1)'),ones(1,27)), zeros(1, 100)];
% AtestCol1_t = timeseries(AtestCol1);
% 
% AtestCol2 = [zeros(1,27),kron(fliplr(A(:,2)'),ones(1,27)), zeros(1, 100)]; 
% AtestCol2_t = timeseries(AtestCol2);
% 
% I = [1 0;
%      0 1];
%  
% Icol1_t = timeseries([zeros(1,54),kron(fliplr(I(:,1)'),ones(1,27)), zeros(1, 100)]);
% Icol2_t = timeseries([zeros(1,81),kron(fliplr(I(:,2)'),ones(1,27)), zeros(1, 100)]);
 