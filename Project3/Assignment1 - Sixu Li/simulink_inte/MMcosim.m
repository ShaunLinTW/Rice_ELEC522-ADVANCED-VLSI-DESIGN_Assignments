MA = rand(4,4) *2;
MB = rand(4,4) *2;
simstep = 59;

AI1 = zeros(1,60);
AI2 = zeros(1,60);
AI3 = zeros(1,60);
AI4 = zeros(1,60);
BI1 = zeros(1,60);
BI2 = zeros(1,60);
BI3 = zeros(1,60);
BI4 = zeros(1,60);

ida = [1,2,3,4,1,2,3,4,1,2,3,4,1,2,3,4];

for i = 1:1:16
    idx = ida(i);
    AI1(i) = MA(idx,1);
    AI2(i) = MA(idx,2);
    AI3(i) = MA(idx,3);
    AI4(i) = MA(idx,4);
    BI1(i) = MB(1,idx);
    BI2(i) = MB(2,idx);
    BI3(i) = MB(3,idx);
    BI4(i) = MB(4,idx);
end

A1.time = 0:1:simstep;
A2.time = 0:1:simstep;
A3.time = 0:1:simstep;
A4.time = 0:1:simstep;
B1.time = 0:1:simstep;
B2.time = 0:1:simstep;
B3.time = 0:1:simstep;
B4.time = 0:1:simstep;


A1.signals.dimensions = 1;
A2.signals.dimensions = 1;
A3.signals.dimensions = 1;
A4.signals.dimensions = 1;
B1.signals.dimensions = 1;
B2.signals.dimensions = 1;
B3.signals.dimensions = 1;
B4.signals.dimensions = 1;


A1.signals.values = AI1';
A2.signals.values = AI2';
A3.signals.values = AI3';
A4.signals.values = AI4';
B1.signals.values = BI1';
B2.signals.values = BI2';
B3.signals.values = BI3';
B4.signals.values = BI4';


out = sim('PEArray_co_sim',40);