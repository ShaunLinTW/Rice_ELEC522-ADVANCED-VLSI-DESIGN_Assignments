%b_matrix = [1 2 3 4; 5 6 7 8; 9 10 11 12; 13 14 15 16 ];
b_matrix = [1 0 0 0; 2 0 0 0; 3 0 0 0; 4 0 0 0];
%b_matrix = [1 2 ; 3 4];
%b_matrix = [1 1 1 1; 1 1 1 1; 1 1 1 1; 1 1 1 1];
b_matrixTranspose = b_matrix'; %Taking tranpose of second matrix since the columns are passed through

%Each column of the initial matrix is first isolated, diagonalized with the
%correct number of zeroes, and accumulated/concatenated into a final matrix (b_signals)
b_signals = zeros(size(b_matrixTranspose,1),2*length(b_matrixTranspose)-1); %Final zero matrix to accumulate all diagonalized matrices
b_colTempAdj = []; %Adjusted Temporary Column Vector matrix i.e. diagonalized

%Iterate through each column to isolate columns (b_col)
for m = 1:length(b_matrixTranspose)
    b_col = diag(b_matrixTranspose(:,m)); %Diagonalizing the isolated column from original matrix

    %The final square matrix must be of size 2n-1, where n = size of the original matrix i.e., n x n matrix
    %The required number of zero fill on either side of the matrix is
    %dependent on its column index.
    %All zero filled matrices must have same number of rows as initial
    %matrix
    %Number of columns (leftPad) = ColumnIndex - 1
    %Number of columns (rightPad) = Size of original matrix - ColumnIndex
    %See notes below for explanation
    requiredZeroFillLeft = zeros(size(b_matrixTranspose,1), m-1 );
    requiredZeroFillRight = zeros(size(b_matrixTranspose,1), size(b_matrixTranspose,1)-m); %Zero filled matrix on right side of the matrix

    b_colTempAdj = cat(2, requiredZeroFillLeft, b_col, requiredZeroFillRight); %Concatenate zerofilled matrices to both ends of diagonalized matrix
    b_signals = b_signals+b_colTempAdj; %Accumulate all adjusted diagonalized matrices
end 
tenFill = zeros(size(b_signals,1), 8-length(b_signals));
b_signals = cat(2, b_signals, tenFill)

%Creating individual structs to stream final, diagonalized matrix into the
%system generator input gateways
b1 = b_signals(1,:);
b1_var.time = 0:1:length(b_signals)-1;
b1_var.signals.values = b1';
b1_var.signals.dimensions = 1;

b2 = b_signals(2,:);
b2_var.time = 0:1:length(b_signals)-1;
b2_var.signals.values = b2';
b2_var.signals.dimensions = 1;

b3 = b_signals(3,:);
b3_var.time = 0:1:length(b_signals)-1;
b3_var.signals.values = b3';
b3_var.signals.dimensions = 1;

b4 = b_signals(4,:);
b4_var.time = 0:1:length(b_signals)-1;
b4_var.signals.values = b4';
b4_var.signals.dimensions = 1;

%_____________________________________________________________________________________________
% We need in total: 2n-1 elements, where n = size of the original matrix i.e., n x n matrix
% 
% 1 2
% 3 4
% 
% => Diagonalizing
% 1 0 + 2 0 
% 0 3   0 4
% 
% => Padding
% 1 0 0 + 0 2 0 
% 0 3 0   0 0 4
% 
% ColumnIndex	LeftPad	RightPad
% 1		        0		1	
% 2		        1		0
% 
% ------------------------------------------------------------------------------------------------------
% We need in total: 2n-1 elements, where n = size of the original matrix i.e., n x n matrix
% 
% 1  2  3  4
% 5  6  7  8 
% 9 10 11 12
% 
% => 
% 1 0 0  +  2 0 0  +  3 0 0  +  4 0 0  
% 0 5 0     0 6 0     0 7 0     0 8 0
% 0 0 9     0 0 10    0 0 11    0 0 12
% 
% =>
% 1 0 0 0 0 0  +  0 2 0 0  0 0  +  0 0 3 0 0  0  +  0 0 0 4 0 0  
% 0 5 0 0 0 0     0 0 6 0  0 0     0 0 0 7 0  0     0 0 0 0 8 0
% 0 0 9 0 0 0     0 0 0 10 0 0     0 0 0 0 11 0     0 0 0 0 0 12
% 
% ColumnIndex	LeftPad	RightPad
% 1		    0		3	
% 2		    1		2
% 3		    2		1
% 4		    3		0