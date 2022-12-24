Q = zeros(4,4);
R = zeros(4,4);

R(1,1) = nonzeros(out.simout12.Data)
R(1,2) = nonzeros(out.simout20.Data)
R(1,3) = nonzeros(out.simout21.Data)
R(1,4) = nonzeros(out.simout22.Data)

R(2,2) = nonzeros(out.simout23.Data)
R(2,3) = nonzeros(out.simout24.Data)
R(2,4) = nonzeros(out.simout25.Data)

R(3,3) = nonzeros(out.simout26.Data)
R(3,4) = nonzeros(out.simout27.Data)

R(4,4) = nonzeros(out.simout40.Data)
%out.simout12(out.simout12~=0)

Q(1,1) = nonzeros(out.simout28.Data)
Q(1,2) = nonzeros(out.simout32.Data)
Q(1,3) = nonzeros(out.simout36.Data)
Q(1,4) = nonzeros(out.simout41.Data)

Q(2,1) = nonzeros(out.simout29.Data)
Q(2,2) = nonzeros(out.simout33.Data)
Q(2,3) = nonzeros(out.simout37.Data)
Q(2,4) = nonzeros(out.simout42.Data)

Q(3,1) = nonzeros(out.simout30.Data)
Q(3,2) = nonzeros(out.simout34.Data)
Q(3,3) = nonzeros(out.simout38.Data)
Q(3,4) = nonzeros(out.simout43.Data)

Q(4,1) = nonzeros(out.simout31.Data)
Q(4,2) = nonzeros(out.simout35.Data)
Q(4,3) = nonzeros(out.simout39.Data)
Q(4,4) = nonzeros(out.simout44.Data)