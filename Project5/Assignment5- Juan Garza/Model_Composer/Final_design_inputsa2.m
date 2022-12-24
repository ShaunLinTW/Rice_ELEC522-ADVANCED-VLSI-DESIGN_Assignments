pad_z = 25;
z = zeros(1,pad_z-1);

pad_z_1 = 24;
z_1 = zeros(1,pad_z_1-1);

rst_m =[0 0 0 0 0 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z 0 z z z z z z z z z z z z z z z ]

%A1
start_m = [ z z 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 z z z z z z z z z z z z z z z z z z z z  z   z z z z z z z z z z]

a11m = [0.1845 0.1845 0.1845 0 0 0 0 z z z z z z z z z z z z z z z z z z z z z z z  0.1845 z z z z]

a21m = [0.6496 0.6496 0.6496 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z z z z 0.6496 z z z ]

a31m = [0.1345 0.1345 0.1345 0.1345 0.1345 0.1345 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z  z z  z 0.1345 z z z z]

a41m = [ 0.9629 0.9629 0.9629 0.9629 0.9629 0.9629 z z z z z z z z z z z z z z z z z z z z z z z 0.9629 z z z z]
%row 2
a12m = [0 0 0 0 0.7026 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z          z z z   0.7026 z z z z]

a22m = [0 0 0 0 0.9529 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z z z z 0.9529 z z z ]

a32m = [0 0 0 0 0.5616 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z z z z 0.5616 z z z]

a42m = [0 0 0 0 0.2118 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z z z z 0.2118 z z z]

%row 3
a13m = [0 0 0 0 0.7124 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z  z z z 0.7124 z z z ]

a23m = [0 0 0 0 0.7813 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z   z z z 0.7813 z z z]

a33m = [0 0 0 0 0.1008 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z   z z z 0.1008 z z z]

a43m = [0 0 0 0 0.8349 0 0 0 0 z z z z z z z z z z z z z z z z z z z z  z z z 0.8349 z z z z]

%row 4
a14m = [0 0 0 0 0.6811 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z  z z z 0.6811 z z z ]

a24m = [0 0 0 0 0.9617 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z z z z 0.9617 z z z ]

a34m = [0 0 0 0 0.9517 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z  z z z 0.9517 z z z ]

a44m = [0 0 0 0  0.4713 0 0 0 0 0 z z z z z z z z z z z z z z z z z z z z  z z z 0.4713 z z z ]

%row 1
a1 = a11m(1,:);
a11_var.time =   0:1:length(a11m)-1;
a11_var.signals.dimensions = 1;
a11_var.signals.values =    a1';

a21 = a21m(1,:);
a21_var.time =   0:1:length(a21m)-1;
a21_var.signals.dimensions = 1;
a21_var.signals.values =    a21';

a31 = a31m(1,:);
a31_var.time =   0:1:length(a31m)-1;
a31_var.signals.dimensions = 1;
a31_var.signals.values =    a31';

a41 = a41m(1,:);
a41_var.time =   0:1:length(a41m)-1;
a41_var.signals.dimensions = 1;
a41_var.signals.values =    a41';


%row 2
a12 = a12m(1,:);
a12_var.time =   0:1:length(a12m)-1;
a12_var.signals.dimensions = 1;
a12_var.signals.values =    a12';

a22 = a22m(1,:);
a22_var.time =   0:1:length(a22m)-1;
a22_var.signals.dimensions = 1;
a22_var.signals.values =    a22';

a32 = a32m(1,:);
a32_var.time =   0:1:length(a32m)-1;
a32_var.signals.dimensions = 1;
a32_var.signals.values =    a32';

a42 = a42m(1,:);
a42_var.time =   0:1:length(a42m)-1;
a42_var.signals.dimensions = 1;
a42_var.signals.values =    a42';


%row 3
a13 = a13m(1,:);
a13_var.time =   0:1:length(a13m)-1;
a13_var.signals.dimensions = 1;
a13_var.signals.values =    a13';

a23 = a23m(1,:);
a23_var.time =   0:1:length(a23m)-1;
a23_var.signals.dimensions = 1;
a23_var.signals.values =    a23';

a33 = a33m(1,:);
a33_var.time =   0:1:length(a33m)-1;
a33_var.signals.dimensions = 1;
a33_var.signals.values =    a33';

a43 = a43m(1,:);
a43_var.time =   0:1:length(a43m)-1;
a43_var.signals.dimensions = 1;
a43_var.signals.values =    a43';


%row 4
a14 = a14m(1,:);
a14_var.time =   0:1:length(a14m)-1;
a14_var.signals.dimensions = 1;
a14_var.signals.values =    a14';

a24 = a24m(1,:);
a24_var.time =   0:1:length(a24m)-1;
a24_var.signals.dimensions = 1;
a24_var.signals.values =    a24';

a34 = a34m(1,:);
a34_var.time =   0:1:length(a34m)-1;
a34_var.signals.dimensions = 1;
a34_var.signals.values =    a34';

a44 = a44m(1,:);
a44_var.time =   0:1:length(a44m)-1;
a44_var.signals.dimensions = 1;
a44_var.signals.values =    a44';









start1 = start_m(1,:);
start_var.time =   0:1:length(start_m)-1;
start_var.signals.dimensions = 1;
start_var.signals.values =    start1';

rst1 = rst_m(1,:);
rst_var.time =   0:1:length(rst_m)-1;
rst_var.signals.dimensions = 1;
rst_var.signals.values =    rst1';














%Old vars down here 
a_m1 = [0.8799 z      0.3401 z 0.3784 z 0.6900 z 0 z z z z z z z  ]
a_m2 = [       z      0.3194 z 0.8434 z 0.2577 z 0.5054 z 0      z z z z z z z z 0 ]
a_m3 = [       z             z 0.9805 z 0.0687 z 0.2073 z 0.5914 z 0      z z z z z z z z]
a_m4 = [       z             z        z 0.0850 z 0.4099 z 0.6262 z 0.5547 z 0      z z z z z z z z]
i_m1 = [       z             z        z        z 1      z 0      z 0      z 0      z 0     z 0      z 0 z 0 z]
i_m2 = [       z             z        z        z        z 0      z 1      z 0      z 0     z 0      z 0 z 0 z 0 z ]
i_m3 = [       z             z        z        z z      z 0      z 0      z 1      z 0     z 0      z 0 z 0 z 0 z 0 z 0 z]
i_m4 = [       z             z        z        z z z    z 0      z 0      z 0      z 1     z 0      z 0 z 0 z 0 z 0 z 0 z]

a1 = a_m1(1,:);
a1_var.time =   0:1:length(a_m1)-1;
a1_var.signals.dimensions = 1;
a1_var.signals.values =    a1';

a2 = a_m2(1,:);
a2_var.time =   0:1:length(a_m2)-1;
a2_var.signals.dimensions = 1;
a2_var.signals.values =    a2';


a3 = a_m3(1,:);
a3_var.time =   0:1:length(a_m3)-1;
a3_var.signals.dimensions = 1;
a3_var.signals.values =    a3';

a4 = a_m4(1,:);
a4_var.time =   0:1:length(a_m4)-1;
a4_var.signals.dimensions = 1;
a4_var.signals.values =    a4';



i1 = i_m1(1,:);
i1_var.time =   0:1:length(i_m1)-1;
i1_var.signals.dimensions = 1;
i1_var.signals.values =    i1';

i2 = i_m2(1,:);
i2_var.time =   0:1:length(i_m2)-1;
i2_var.signals.dimensions = 1;
i2_var.signals.values =    i2';

i3 = i_m3(1,:);
i3_var.time =   0:1:length(i_m3)-1;
i3_var.signals.dimensions = 1;
i3_var.signals.values =    i3';

i4 = i_m4(1,:);
i4_var.time =   0:1:length(i_m4)-1;
i4_var.signals.dimensions = 1;
i4_var.signals.values =    i4';






