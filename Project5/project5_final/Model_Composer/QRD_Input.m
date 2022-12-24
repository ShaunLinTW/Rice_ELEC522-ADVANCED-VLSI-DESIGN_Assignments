% Clears all variables previously assigned.
clear
% Closes all graphs and windows open.
close all

latency = 42;   % check the latency value from Vitis HLS synthesis results.
gap = (latency*5) + 4;

rst_val = [zeros(1,(latency*4)+3), 1, zeros(1,gap), 1, zeros(1,latency)];
rst = timeseries(rst_val);

A1 = [0.6900 0.5054 0.5914 0.5547;     % A1 Matrix
      0.3784 0.2577 0.2073 0.6262; 
      0.3401 0.8438 0.0687 0.4099; 
      0.8799 0.3194 0.9805 0.0850];
  
A2 = [0.3564 0.7160 0.9118 0.0091;     % A2 Matrix
      0.8255 0.3252 0.0785 0.0412; 
      0.6638 0.5491 0.9037 0.3417; 
      0.7119 0.4366 0.7662 0.6734];

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