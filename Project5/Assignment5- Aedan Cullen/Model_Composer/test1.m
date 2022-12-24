global col1_in
global col2_in
global col3_in
global col4_in

mat1 = [
    0.6900 0.5054 0.5914 0.5547 1 0 0 0
    0.3784 0.2577 0.2073 0.6262 0 1 0 0
    0.3401 0.8438 0.0687 0.4099 0 0 1 0
    0.8799 0.3194 0.9805 0.0850 0 0 0 1
];
mat1 = [
    0.7 0.6 0.5 0.4 1 0 0 0
    0.3 0.2 0.1 0.9 0 1 0 0
    1.1 1.2 1.3 1.4 0 0 1 0
    1.5 1.6 1.7 1.8 0 0 0 1
];
n = din(mat1);

disp("Done setting matrix inputs; run Simulink now and then press Enter");
pause;

disp("Accelerator results:");
result = dout(n, out);
acR = result(1:4, 1:4);
acQ = result(1:4, 5:8);
disp([acQ, acR])

disp(acQ*acR)

disp("MATLAB results:");
[Q, R] = qr(mat1(1:4, 1:4));
disp([Q, R]);

disp(Q*R);