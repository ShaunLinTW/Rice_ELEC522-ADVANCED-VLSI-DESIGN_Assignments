MA = rand(4,4) *2;
MB = rand(4,1) *2;
simstep = 14;

AI1 = [MA(1,:),0,0,0,0,0,0,0,0,0,0,0];
AI2 = [0,MA(2,:),0,0,0,0,0,0,0,0,0,0];
AI3 = [0,0,MA(3,:),0,0,0,0,0,0,0,0,0];
AI4 = [0,0,0,MA(4,:),0,0,0,0,0,0,0,0];
BI1 = [MB(:,1)',0,0,0,0,0,0,0,0,0,0,0];
BI2 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
BI3 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
BI4 = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
ENI = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
CLI = [0,1,0,0,0,0,0,0,0,0,0,0,0,0,0];
PPI = [1,1,1,1,1,1,1,1,1,1,1,0,1,1,1];
CSI = [0,0,0,0,0,0,0,0,0,0,0,1,1,1,1];

A1.time = 0:1:simstep;
A2.time = 0:1:simstep;
A3.time = 0:1:simstep;
A4.time = 0:1:simstep;
B1.time = 0:1:simstep;
B2.time = 0:1:simstep;
B3.time = 0:1:simstep;
B4.time = 0:1:simstep;
EN.time = 0:1:simstep;
CL.time = 0:1:simstep;
PP.time = 0:1:simstep;
CS.time = 0:1:simstep;

A1.signals.dimensions = 1;
A2.signals.dimensions = 1;
A3.signals.dimensions = 1;
A4.signals.dimensions = 1;
B1.signals.dimensions = 1;
B2.signals.dimensions = 1;
B3.signals.dimensions = 1;
B4.signals.dimensions = 1;
EN.signals.dimensions = 1;
CL.signals.dimensions = 1;
PP.signals.dimensions = 1;
CS.signals.dimensions = 1;

A1.signals.values = AI1';
A2.signals.values = AI2';
A3.signals.values = AI3';
A4.signals.values = AI4';
B1.signals.values = BI1';
B2.signals.values = BI2';
B3.signals.values = BI3';
B4.signals.values = BI4';
EN.signals.values = ENI';
CL.signals.values = CLI';
PP.signals.values = PPI';
CS.signals.values = CSI';

out = sim('PEArray_func_sim',15);

oS1 = out.S1.Data';
oS2 = out.S2.Data';
oS3 = out.S3.Data';
oS4 = out.S4.Data';

O = [oS1(1,16);
     oS2(1,16);
     oS3(1,16);
     oS4(1,16)];
G = MA * MB;
E = G - O;
relativeErr = abs(E) ./ abs(G);
disp("relative error on each position:");
disp(relativeErr);