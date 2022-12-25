A1 = [0.6900 0.5054 0.5914 0.5547;
      0.3784 0.2577 0.2073 0.6262; 
      0.3401 0.8438 0.0687 0.4099; 
      0.8799 0.3194 0.9805 0.0850];
A2 = [0.1 0.1 0.4 0.3; 
     0.2 0.8 0.6 0.5; 
     0.9 0.1 0.3 .2; 
     0.3 0.1 0.4 0.6];
b1 = [0.4;
      0.2; 
      0.9; 
      0.5];
b2 = [0.2; 
     0.1; 
     0.8; 
     0.4];
 %--------------Run simulation for A1 Matrix-----------------
disp("Run Simulation for A1*x = b1");
[Q, R] = qr(A1)
QT = Q'
y = QT * b1
size = 4;
x = zeros(size,1)
c = cond(A1)
if (R(size, size) == 0) error('Matrix is singular!'); end;
x(4) = y(4)/R(4,4)
x(3) = (y(3) - (R(3,4) * x(4))) / R(3,3)
x(2) = (y(2) - (R(2,3) * x(3)) - (R(2,4) * x(4))) / R(2,2)
x(1) = (y(1) - (R(1,2) * x(2)) - (R(1,3) * x(3)) - (R(1,4) * x(4))) / R(1,1)
 %--------------Run simulation for A2 Matrix-----------------
disp("Run Simulation for A2*x = b2");
[Q, R] = qr(A2)
QT = Q'
y = QT * b2
size = 4;
x = zeros(size,1)
c = cond(A2)
if (R(size, size) == 0) error('Matrix is singular!'); end;
x(4) = y(4)/R(4,4)
x(3) = (y(3) - (R(3,4) * x(4))) / R(3,3)
x(2) = (y(2) - (R(2,3) * x(3)) - (R(2,4) * x(4))) / R(2,2)
x(1) = (y(1) - (R(1,2) * x(2)) - (R(1,3) * x(3)) - (R(1,4) * x(4))) / R(1,1)