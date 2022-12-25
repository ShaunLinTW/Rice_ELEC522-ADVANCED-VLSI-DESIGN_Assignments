Vectoroutput = [out.R1.data(198)' out.R1.data(199)' out.R1.data(200)' out.R1.data(201)'];
B = [out.R2.data(197)' out.R2.data(198)' out.R2.data(199)' out.R2.data(200)'];
C = [out.R3.data(196)' out.R3.data(197)' out.R3.data(198)' out.R3.data(199)'];
D = [out.R4.data(195)' out.R4.data(196)' out.R4.data(197)' out.R4.data(198)'];

R=[Vectoroutput;B;C;D];
Vectoroutput1 = [out.y1.data(198)'];
B1 = [out.y2.data(198)'];
C1 = [out.y3.data(198)'];
D1 = [out.y4.data(198)'];
Y=[Vectoroutput1;B1;C1;D1];


  fprintf('the Y is.\n');
  disp (Y);
  fprintf('the R is.\n');
  disp (R);
  

