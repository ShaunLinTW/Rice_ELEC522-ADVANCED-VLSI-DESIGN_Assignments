% Clears all variables previously assigned.
clear
% Closes all graphs and windows open.
close all

latency = 42;   % check the latency value from Vitis HLS synthesis results.
gap = (latency*5) + 4;

rst_val = [zeros(1,(latency*4)+3), 1, zeros(1,gap), 1, zeros(1,latency)];
rst = timeseries(rst_val);

A1 = [0.6900 0.5054 0.5914 0.5547;     % A1 Matrix <- Input your A1 Matrix here
      0.3784 0.2577 0.2073 0.6262; 
      0.3401 0.8438 0.0687 0.4099; 
      0.8799 0.3194 0.9805 0.0850];

A2 = [0.1 0.1 0.4 0.3;                 % A2 Matrix <- Input your A2 Matrix here
      0.2 0.8 0.6 0.5; 
      0.9 0.1 0.3 0.2; 
      0.3 0.1 0.4 0.6];
  
A = [0.1 0.1 0.4 0.3;                 % A test Matrix
     0.2 0.8 0.6 0.5; 
     0.9 0.1 0.3 0.2; 
     0.3 0.1 0.4 0.6];

b1 = [0.4;                             % b1 Matrix
      0.2; 
      0.9; 
      0.5];

b2 = [0.2;                             % b2 Matrix
      0.1; 
      0.8; 
      0.4];
  
b = [0.2;                             % b test Matrix
     0.1; 
     0.8; 
     0.4];
A = timeseries([A(1,1), A(1,2), A(1,3), A(1,4), A(2,1), A(2,2), A(2,3), A(2,4), A(3,1), A(3,2), A(3,3), A(3,4), A(4,1), A(4,2), A(4,3), A(4,4)]);
b = timeseries([b(1,1), b(2,1), b(3,1), b(4,1)]);

a1_1 = [A1(4,1), zeros(1,latency), A1(3,1), zeros(1,latency), A1(2,1), zeros(1,latency), A1(1,1), zeros(1,(latency*2)+1)];
a1_2 = [A2(4,1), zeros(1,latency), A2(3,1), zeros(1,latency), A2(2,1), zeros(1,latency), A2(1,1), zeros(1,latency)];
a2_1 = [zeros(1,latency), A1(4,2), zeros(1,latency), A1(3,2), zeros(1,latency), A1(2,2), zeros(1,latency), A1(1,2), zeros(1,(latency*2)+1)];
a2_2 = [A2(4,2), zeros(1,latency), A2(3,2), zeros(1,latency), A2(2,2), zeros(1,latency), A2(1,2), zeros(1,latency)];
a3_1 = [zeros(1,latency*2), A1(4,3), zeros(1,latency), A1(3,3), zeros(1,latency), A1(2,3), zeros(1,latency), A1(1,3), zeros(1,(latency*2)+1)];
a3_2 = [A2(4,3), zeros(1,latency), A2(3,3), zeros(1,latency), A2(2,3), zeros(1,latency), A2(1,3), zeros(1,latency)];
a4_1 = [zeros(1,latency*3), A1(4,4), zeros(1,latency), A1(3,4), zeros(1,latency), A1(2,4), zeros(1,latency), A1(1,4), zeros(1,(latency*2)+1)];
a4_2 = [A2(4,4), zeros(1,latency), A2(3,4), zeros(1,latency), A2(2,4), zeros(1,latency), A2(1,4), zeros(1,latency)];
A_col1 = timeseries([a1_1, a1_2]);
A_col2 = timeseries([a2_1, a2_2]);
A_col3 = timeseries([a3_1, a3_2]);
A_col4 = timeseries([a4_1, a4_2]);

b1_col = [zeros(1,(latency*8)+3), b1(4,1), zeros(1,latency-1), b1(3,1), zeros(1,latency-1), b1(2,1), zeros(1,latency-1), b1(1,1), zeros(1,(latency*2)+4)];
b2_col = [b2(4,1), zeros(1,latency-1), b2(3,1), zeros(1,latency-1), b2(2,1), zeros(1,latency-1), b2(1,1), zeros(1,latency)];
b_col = timeseries([b1_col, b2_col]);

I = [1 0 0 0;   % Identity matrix
     0 1 0 0; 
     0 0 1 0; 
     0 0 0 1];

i1 = [zeros(1,latency*4), I(1,1), zeros(1,gap), I(1,1), zeros(1,latency)];
i2 = [zeros(1,(latency*6)+1), I(2,2), zeros(1,gap), I(2,2), zeros(1,latency)];
i3 = [zeros(1,(latency*8)+2), I(3,3), zeros(1,gap), I(3,3), zeros(1,latency)];
i4 = [zeros(1,(latency*10)+3), I(4,4), zeros(1,gap), I(4,4), zeros(1,latency)];
I_col1 = timeseries(i1);
I_col2 = timeseries(i2);
I_col3 = timeseries(i3);
I_col4 = timeseries(i4);
disp('A1 Matrix:');
disp(A1);
disp('A2 Matrix:');
disp(A2);
disp('b1 Vector');
disp(b1);
disp('b2 Vector');
disp(b2);