MA = rand(4,4) *2;
MB = rand(4,4) *2;
simstep = 14;

AI1 = [MA(1,:),0,0,0,0,0,0,0,0,0,0,0];
AI2 = [0,MA(2,:),0,0,0,0,0,0,0,0,0,0];
AI3 = [0,0,MA(3,:),0,0,0,0,0,0,0,0,0];
AI4 = [0,0,0,MA(4,:),0,0,0,0,0,0,0,0];
BI1 = [MB(:,1)',0,0,0,0,0,0,0,0,0,0,0];
BI2 = [0,MB(:,2)',0,0,0,0,0,0,0,0,0,0];
BI3 = [0,0,MB(:,3)',0,0,0,0,0,0,0,0,0];
BI4 = [0,0,0,MB(:,4)',0,0,0,0,0,0,0,0];
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

out = sim('PEArray_co_sim',15);

oS1 = out.S1.Data';
oS2 = out.S2.Data';
oS3 = out.S3.Data';
oS4 = out.S4.Data';
oS5 = out.S5.Data';
oS6 = out.S6.Data';
oS7 = out.S7.Data';
oS8 = out.S8.Data';

O = [flip(oS1(1,13:end));
     flip(oS2(1,13:end));
     flip(oS3(1,13:end));
     flip(oS4(1,13:end))];
H = [flip(oS5(1,13:end));
     flip(oS6(1,13:end));
     flip(oS7(1,13:end));
     flip(oS8(1,13:end))];
G = MA * MB;
Es = G - O;
Eh = G - H;
relativeErrS = abs(Es) ./ abs(G);
relativeErrH = abs(Eh) ./ abs(G);
disp("relative error on each position func simulation:");
disp(relativeErrS);
disp("relative error on each position jtag simulation:");
disp(relativeErrH);
disp("func & jtag simulation diff");
disp(O - H)