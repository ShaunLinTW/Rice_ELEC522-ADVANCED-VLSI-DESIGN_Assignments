% clc;clear;
A1 = [[0.8799 0.3194 0.9805 0.0850];
    [0.3401 0.8438 0.0687 0.4099];
    [0.3784 0.2577 0.2073 0.6262];
    [0.6900 0.5054 0.5914 0.5547]];
% A = abs(rand(4,4));
% A = A * A';
[q1,r1] = qr(A1);
q1 = q1';

A2=[[0.7241    0.5470    0.2991    0.5388];
    [0.5470    0.4991    0.1706    0.4716];
    [0.2991    0.1706    0.1898    0.1337];
    [0.5388    0.4716    0.1337    0.5239]];
[q2,r2] = qr(A2);
q2 = q2';

qc = zeros(4,4);
rc = zeros(4,4);

SlxA = timeseries(A(:,1));
SlxB = timeseries([0 A(:,2)']');
SlxC = timeseries([0 0 A(:,3)']');
SlxD = timeseries([0 0 0 A(:,4)']');
SlxQ1 = timeseries([0 0 0 0 1 0]);
SlxQ2 = timeseries([0 0 0 0 0 0 1 0]);
SlxQ3 = timeseries([0 0 0 0 0 0 0 0 1 0]);
SlxQ4 = timeseries([0 0 0 0 0 0 0 0 0 0 1 0]);

R = [
    [out.simout3.Data(5),out.simout6.Data(6),out.simout1.Data(7),out.simout7.Data(8) ],
    [0,out.simout2.Data(9),out.simout16.Data(10),out.simout11.Data(11) ],
    [0,0,out.simout10.Data(10),out.simout13.Data(11) ],
    [0,0,0,out.simout14.Data(13) ]
];
Q = [
    [0.7161, 0.2779, 0.3085, 0.5608],
    [-0.4043, 0.9123, 0.003414, 0.06235],
    [0.3971, 0.1864, -0.8904, -0.1094],
    [-0.3987, -0.2319, -0.3117, 0.7993]
];