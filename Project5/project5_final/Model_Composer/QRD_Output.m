Q1_col1 = downsample(out.out_Q_col1(340:466),42);
Q1_col2 = downsample(out.out_Q_col2(382:508),42);
Q1_col3 = downsample(out.out_Q_col3(424:550),42);
Q1_col4 = downsample(out.out_Q_col4(424:550),42);

Q2_col1 = downsample(out.out_Q_col1(555:end),42);
Q2_col2 = downsample(out.out_Q_col2(597:end),42);
Q2_col3 = downsample(out.out_Q_col3(639:end),42);
Q2_col4 = downsample(out.out_Q_col4(639:end),42);

R1_row1 = downsample(out.out_R_row1(172:466),42);
R1_row2 = downsample(out.out_R_row2(256:508),42);
R1_row3 = downsample(out.out_R_row3(340:550),42);
R1_row4 = out.out_R_row4(382);

R2_row1 = downsample(out.out_R_row1(387:end),42);
R2_row2 = downsample(out.out_R_row2(471:end),42);
R2_row3 = downsample(out.out_R_row3(555:end),42);
R2_row4 = out.out_R_row4(597);

R1 = [R1_row1(1:4)'; [0 R1_row2(1:3)']; [0 0 R1_row3(1:2)']; [0 0 0 R1_row4(1)']];
Q1 = [Q1_col1(1:4)'; Q1_col2(1:4)'; Q1_col3(1:4)'; Q1_col4(1:4)']';
disp('Q1:');
disp(flip(Q1));
disp('R1:');
disp(R1);

R2 = [R2_row1(1:4)'; [0 R2_row2(1:3)']; [0 0 R2_row3(1:2)']; [0 0 0 R2_row4(1)']];
Q2 = [Q2_col1(1:4)'; Q2_col2(1:4)'; Q2_col3(1:4)'; Q2_col4(1:4)']';
disp('Q2:');
disp(flip(Q2));
disp('R2:');
disp(R2);

A1 = [0.6900 0.5054 0.5914 0.5547;     % A1 Matrix
      0.3784 0.2577 0.2073 0.6262; 
      0.3401 0.8438 0.0687 0.4099; 
      0.8799 0.3194 0.9805 0.0850];
  
A2 = [0.3564 0.7160 0.9118 0.0091;     % A2 Matrix
      0.8255 0.3252 0.0785 0.0412; 
      0.6638 0.5491 0.9037 0.3417; 
      0.7119 0.4366 0.7662 0.6734];

A1_expected = Q1*R1;
error = sum(sum(abs(A1 - A1_expected)));
disp('error for A1 Matrix: ');
disp(error);

A2_expected = Q2*R2;
error = sum(sum(abs(A2 - A2_expected)));
disp('error for A2 Matrix: ');
disp(error);