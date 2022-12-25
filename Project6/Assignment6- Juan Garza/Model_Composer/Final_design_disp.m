buffer = 25;

%a_11  = transpose(out.a_11_debug.DATA(1:490))%.'; %t_out
r1_11 =  out.a_11.DATA(400).';
%r2_11 =  out.a_11.DATA(1500).';

%a_12  = transpose(out.a_12.DATA(1:190))%.'; %t_out
%a_13  = transpose(out.a_13.DATA(1:190))%.'; %t_out
%a_14  = transpose(out.a_14.DATA(1:190))%.'; %t_out


%a_21  = transpose(out.a_21.DATA(1:590))%.'; %t_out
r1_21 =  out.a_21.DATA(400).';
%r2_21 =  out.a_21.DATA(1500).';

%a_22  = transpose(out.a_22.DATA(1:590))%.'; %t_out
r1_22 =  out.a_22.DATA(400).';
%r2_22 =  out.a_22.DATA(1500).';
%a_23  = transpose(out.a_23.DATA(1:190))%.'; %t_out
%a_24  = transpose(out.a_24.DATA(1:190))%.'; %t_out

%a_31  = transpose(out.a_31.DATA(1:590))%.'; %t_out
r1_31 =  out.a_31.DATA(400).';
%r2_31 =  out.a_31.DATA(1500).';



%a_32  = transpose(out.a_32.DATA(1:590))%.'; %t_out
r1_32 =  out.a_32.DATA(400).';
%r2_32 =  out.a_32.DATA(1500).';


%a_33  = transpose(out.a_33.DATA(1:590))%.'; %t_out
r1_33 =  out.a_33.DATA(400).';
%r2_33 =  out.a_33.DATA(1500).';


%a_34  = transpose(out.a_34.DATA(1:190))%.'; %t_out

%a_41  = transpose(out.a_41.DATA(1:590))%.'; %t_out
r1_41 =  out.a_41.DATA(400).';
%r2_41 =  out.a_41.DATA(1500).';


%a_42  = transpose(out.a_42.DATA(1:590))%.'; %t_out
r1_42 =  out.a_42.DATA(400).';
%r2_42 =  out.a_42.DATA(1500).';


%a_43  = transpose(out.a_43.DATA(1:590))%.'; %t_out
r1_43 =  out.a_43.DATA(400).';
%r2_43 =  out.a_43.DATA(1500).';
%a_44  = transpose(out.a_44.DATA(1:590))%.'; %t_out
r1_44 =  out.a_44.DATA(400).';
%r2_44 =  out.a_44.DATA(1500).';



%row1
%q_11  = transpose(out.q_11.DATA(1:390))%.'; %t_out
q1_11 =  out.q_11.DATA(400).';
%q2_11 =  out.q_11.DATA(1500).';

%q_21  = transpose(out.q_21.DATA(1:490)).'; %t_out
q1_21 =  out.q_21.DATA(400).';
%q2_21 =  out.q_21.DATA(1500).';

%q_31  = transpose(out.q_31.DATA(1:490)).'; %t_out
q1_31 =  out.q_31.DATA(400).';
%q2_31 =  out.q_31.DATA(1500).';

%q_41  = transpose(out.q_41.DATA(1:490)).'; %t_out
q1_41 =  out.q_41.DATA(400).';
%q2_41 =  out.q_41.DATA(1500).';



%row2
%q_12  = transpose(out.q_12.DATA(1:490)).'; %t_out
q1_12 =  out.q_12.DATA(490).';
%q2_12 =  out.q_12.DATA(1500).';

%q_22  = transpose(out.q_22.DATA(1:490)).'; %t_out
q1_22 =  out.q_22.DATA(490).';
%q2_22 =  out.q_22.DATA(1500).';

%q_32  = transpose(out.q_32.DATA(1:490)).'; %t_out
q1_32 =  out.q_32.DATA(490).';
%q2_32 =  out.q_32.DATA(1500).';
%q_32  = transpose(out.q_32.DATA(1:490))%.'; %t_out
q1_42 =  out.q_42.DATA(490).';
%q2_42 =  out.q_42.DATA(1500).';

%row3
%q_13  = transpose(out.q_13.DATA(1:490)).'; %t_out
q1_13 =  out.q_13.DATA(490).';
%q2_13 =  out.q_13.DATA(1500).';
%q_23  = transpose(out.q_22.DATA(1:490)).'; %t_out
q1_23 =  out.q_23.DATA(490).';
%q2_23 =  out.q_23.DATA(1500).';
%q_33  = transpose(out.q_32.DATA(1:490)).'; %t_out
q1_33 =  out.q_33.DATA(490).';
%q2_33 =  out.q_33.DATA(1500).';
%q_32  = transpose(out.q_32.DATA(1:490))%.'; %t_out
q1_43 =  out.q_43.DATA(490).';
%q2_43 =  out.q_43.DATA(1500).';


%row4
%q_13  = transpose(out.q_13.DATA(1:490)).'; %t_out
q1_14 =  out.q_14.DATA(490).';
%q2_14 =  out.q_14.DATA(1500).';
%q_23  = transpose(out.q_22.DATA(1:490)).'; %t_out
q1_24 =  out.q_24.DATA(490).';
%q2_24 =  out.q_24.DATA(1500).';
%q_34  = transpose(out.q_34.DATA(1:450)).'; %t_out
q1_34 =  out.q_34.DATA(490).';
%q2_34 =  out.q_34.DATA(1500).';
%q_32  = transpose(out.q_32.DATA(1:490))%.'; %t_out
q1_44 =  out.q_44.DATA(490).';
%q2_44 =  out.q_44.DATA(1500).';
%qtb1 =  transpose(out.debug_var.DATA(1:490))

qtb1 =  transpose(out.debug_var.DATA(490));
qtb2 =  transpose(out.debug1_var.DATA(490));
qtb3 =  transpose(out.debug2_var.DATA(490));
qtb4 =  transpose(out.debug3_var.DATA(490));


b1 = [0.2; 0.1; 0.8; 0.4]
b = b1
x4 = qtb4 / r1_44 .';
x3 = (qtb3 - x4* r1_43)/r1_33 .';
x2 = (qtb2 - x3*r1_32 - x4*r1_42)/r1_22 .';
x1 = (qtb1 - x2*r1_21 - x3*r1_31 - x4*r1_41)/r1_11 .';
qtb_disp_hw = transpose([qtb1;qtb2;qtb3;qtb4])

[Q, r] = qr(A)
Ri = [r1_11 r1_21 r1_31 r1_41; 
       0 r1_22 r1_32    r1_42; 
       0  0     r1_33   r1_43; 
       0  0     0        r1_44]
Qi = [q1_11 q1_21 q1_31 q1_41; 
      q1_12 q1_22 q1_32 q1_42; 
      q1_13 q1_23 q1_33 q1_43; 
      q1_14 q1_24 q1_34 q1_44]
Ai = Qi* Ri

A3 = [0.1845 0.7026 0.7124 0.6811;
     0.6496 0.9529 0.7813 0.9637;
     0.1345 0.5616 0.1008 0.9517;
     0.9629 0.2118 0.8349 0.4713];

A = [0.1 0.1 0.4 0.3;
      0.2 0.8 0.6 0.5;
      0.9 0.1 0.3 .2;
      0.3 0.1 0.4 0.6]



Qt = transpose(Q);
qtb = Qt*b ;
qtb_disp = transpose(qtb)

x4sw = qtb(4) / r(4,4) .';
x3sw = (qtb(3) - x4sw* r(3,4))/r(3,3) .';
x2sw = (qtb(2) - x3sw*r(2,3) - x4sw*r(2,4))/r(2,2) .';
x1sw = (qtb(1) - x2sw*r(1,2) - x3sw*r(1,3) - x4sw*r(1,4))/r(1,1) .';
x_v = [x1;x2;x3;x4];
x_vsw = [x1sw;x2sw;x3sw;x4sw];
x_v_disp = transpose(x_v)
x_vsw_disp = transpose(x_vsw)

B_hw_dips = transpose(A*x_v)
B_sw_disp = transpose(A*x_vsw)




x_1 = [0.8034;   -0.3796;    0.2957;    0.1311];
A1 = [0.1 0.1 0.4 0.3;
      0.2 0.8 0.6 0.5;
      0.9 0.1 0.3 .2;
      0.3 0.1 0.4 0.6]
b_1 = A1*x_1;
[Q1, r1] = qr(A1)
b_1_disp = b_1'
qTb_1 = transpose(Q1'*b_1)
x_1disp = x_1'

  
  
x_2 = [-0.606567; 0.377563; 1.02502; 0.0412598];
A2 = [0.6900 0.5054 0.5914 0.5547;
     0.3401 0.8434 0.0687 0.4099;
     0.3784 0.2577 0.2073 0.6262;
     0.8799 0.3194 0.9805 0.0850]
b_2 = A2*x_2;
[Q2, r2] = qr(A2)
b_2_disp = transpose(b_2)
qTb_2 = transpose(Q2'*b_2)
x_2_disp = transpose(x_2)
 

x_3 = [0.8; 0.1; -0.5; 0.7];

A3 = [0.1845 0.7026 0.7124 0.6811;
     0.6496 0.9529 0.7813 0.9637;
     0.1345 0.5616 0.1008 0.9517;
     0.9629 0.2118 0.8349 0.4713]
b_3 = A3*x_3;
b_3_disp = transpose(b_3)
[Q3, r] = qr(A3)
qTb_3 = transpose(Q3'*b_3)
x_3_disp = transpose(x_3)



%aqtb4 =  transpose(out.debug3_var.DATA(380:400))



 %b3 = [0.2; 0.1; 0.4; 0.4]
 %qT3 = A3*b3
 
%R2 = [r2_11 r2_21 r2_31 r2_41; 0 r2_22 r2_32 r2_42; 0 0 r2_33 r2_43; 0 0 0 r2_44]
%Q2 = [q2_11 q2_21 q2_31 q2_41; q2_12 q2_22 q2_32 q2_42; q2_13 q2_23 q2_33 q2_43; q2_14 q2_24 q2_34 q2_44]

%q_12  = transpose(out.q_12.DATA(1:490))%.'; %t_out
%q_13  = transpose(out.q_13.DATA(1:490))%.'; %t_out
%q_14  = transpose(out.q_14.DATA(1:190))%.'; %t_out
%q_21  = transpose(out.q_21.DATA(1:490))%.'; %t_out
%q_22  = transpose(out.q_22.DATA(1:490))%.'; %t_out
%q_23  = transpose(out.q_23.DATA(1:490))%.'; %t_out
%q_24  = transpose(out.q_24.DATA(1:490))%.'; %t_out
%q_31  = transpose(out.q_31.DATA(1:490))%.'; %t_out
%q_32  = transpose(out.q_32.DATA(1:490))%.'; %t_out
%q_33  = transpose(out.q_33.DATA(1:490))%.'; %t_out
%q_34  = transpose(out.q_34.DATA(1:490))%.'; %t_out
%q_41  = transpose(out.q_41.DATA(1:490))%.'; %t_out
%q_42  = transpose(out.q_42.DATA(1:490))%.'; %t_out
%q_43  = transpose(out.q_43.DATA(1:490))%.'; %t_out
%q_44  = transpose(out.q_44.DATA(1:490))%.'; %t_out