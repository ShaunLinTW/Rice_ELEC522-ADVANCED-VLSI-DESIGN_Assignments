A = [1 1 4 3; 
     2 7 6 5; 
     9 10 3 11; 
     16 1 14 13]
[Q, R] = qr(A)
b = [2; 
     10; 
     8; 
     4]
QT = Q'
n = 4
y = QT * b
x=zeros(n,1)
c = cond(A)
if (R(n,n)==0) error('Matrix is singular!'); end;
for j = n:-1:1
    if (R(j,j)==0) error('Matrix is singular!'); end;
    x(j)=y(j)/R(j,j);
    y(1:j-1)=y(1:j-1)-R(1:j-1,j)*x(j);
end

