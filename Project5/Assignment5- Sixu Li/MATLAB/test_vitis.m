a11 = 0.8799; a12 = 0.3194; a13 = 0.9805; a14 = 0.0850; 
a21 = 0.3401; a22 = 0.8438; a23 = 0.0687; a24 = 0.4099; 
a31 = 0.3784; a32 = 0.2577; a33 = 0.2073; a34 = 0.6262; 
a41 = 0.6900; a42 = 0.5054; a43 = 0.5914; a44 = 0.5547;
din = 1.0;

a11 = timeseries([a11]);
a21 = timeseries([a21]);
a31 = timeseries([a31]);
a41 = timeseries([a41]);

a12 = timeseries([a12]);
a22 = timeseries([a22]);
a32 = timeseries([a32]);
a42 = timeseries([a42]);

a13 = timeseries([a13]);
a23 = timeseries([a23]);
a33 = timeseries([a33]);
a43 = timeseries([a43]);

a14 = timeseries([a14]);
a24 = timeseries([a24]);
a34 = timeseries([a34]);
a44 = timeseries([a44]);

din = timeseries([din]);

A = [[0.8799 0.3194 0.9805 0.0850];
    [0.3401 0.8438 0.0687 0.4099];
    [0.3784 0.2577 0.2073 0.6262];
    [0.6900 0.5054 0.5914 0.5547]];
% A = abs(rand(4,4));
% A = A * A';
[q,r] = qr(A);
