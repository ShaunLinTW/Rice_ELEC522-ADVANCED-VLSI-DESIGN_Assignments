buffer = 25;

%a_11  = transpose(out.a_11.DATA(1:490)).'; %t_out
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
q1_12 =  out.q_12.DATA(400).';
%q2_12 =  out.q_12.DATA(1500).';

%q_22  = transpose(out.q_22.DATA(1:490)).'; %t_out
q1_22 =  out.q_22.DATA(400).';
%q2_22 =  out.q_22.DATA(1500).';

%q_32  = transpose(out.q_32.DATA(1:490)).'; %t_out
q1_32 =  out.q_32.DATA(400).';
%q2_32 =  out.q_32.DATA(1500).';
%q_32  = transpose(out.q_32.DATA(1:490))%.'; %t_out
q1_42 =  out.q_42.DATA(400).';
%q2_42 =  out.q_42.DATA(1500).';

%row3
%q_13  = transpose(out.q_13.DATA(1:490)).'; %t_out
q1_13 =  out.q_13.DATA(400).';
%q2_13 =  out.q_13.DATA(1500).';
%q_23  = transpose(out.q_22.DATA(1:490)).'; %t_out
q1_23 =  out.q_23.DATA(400).';
%q2_23 =  out.q_23.DATA(1500).';
%q_33  = transpose(out.q_32.DATA(1:490)).'; %t_out
q1_33 =  out.q_33.DATA(400).';
%q2_33 =  out.q_33.DATA(1500).';
%q_32  = transpose(out.q_32.DATA(1:490))%.'; %t_out
q1_43 =  out.q_43.DATA(400).';
%q2_43 =  out.q_43.DATA(1500).';


%row4
%q_13  = transpose(out.q_13.DATA(1:490)).'; %t_out
q1_14 =  out.q_14.DATA(400).';
%q2_14 =  out.q_14.DATA(1500).';
%q_23  = transpose(out.q_22.DATA(1:490)).'; %t_out
q1_24 =  out.q_24.DATA(400).';
%q2_24 =  out.q_24.DATA(1500).';
%q_34  = transpose(out.q_34.DATA(1:450)).'; %t_out
q1_34 =  out.q_34.DATA(400).';
%q2_34 =  out.q_34.DATA(1500).';
%q_32  = transpose(out.q_32.DATA(1:490))%.'; %t_out
q1_44 =  out.q_44.DATA(400).';
%q2_44 =  out.q_44.DATA(1500).';



Ri = [r1_11 r1_21 r1_31 r1_41; 0 r1_22 r1_32 r1_42; 0 0 r1_33 r1_43; 0 0 0 r1_44]
Qi = [q1_11 q1_21 q1_31 q1_41; q1_12 q1_22 q1_32 q1_42; q1_13 q1_23 q1_33 q1_43; q1_14 q1_24 q1_34 q1_44]

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


