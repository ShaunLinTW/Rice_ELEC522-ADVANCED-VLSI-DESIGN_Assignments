clear all;
clc;
whichClockCycle = 15;

zeroFill = zeros(1, whichClockCycle-1);
a_matrix = [0.8799 zeroFill 0.3401 zeroFill 0.3784 zeroFill 0.69 zeroFill];

a1 = a_matrix(1,:)
a1_var.time = 0:1:length(a_matrix)-1;
a1_var.signals.values = a1';
a1_var.signals.dimensions = 1;

%____________________________________________________________________________________________________________________________________________

clockBaseTime = 1:whichClockCycle*4;
clockBaseValues = zeros(1, whichClockCycle*4);
clockBaseValues(whichClockCycle*1) = 1;
clockBaseValues(whichClockCycle*2) = 1;
clockBaseValues(whichClockCycle*3) = 1;
clockBaseValues(whichClockCycle*4) = 1;

clock_var.time = clockBaseTime;
clock_var.signals.values = clockBaseValues';
clock_var.signals.dimensions = 1;
%____________________________________________________________________________________________________________________________________________
matrix_vector_mode_var.time = [0 1 2 3 4 5 6 7 8 9 10 11 12];
matrix_vector_mode_var.signals.values = [ 0 0 0 0 0 0 0 0 0 0 0 0 0 ]';
%matrix_vector_mode_var.signals.values = [ 1 1 1 1 1 1 1 1 1 1 1 1 1 ]';
matrix_vector_mode_var.signals.dimensions = 1;

%____________________________________________________________________________________________________________________________________________
% a_matrixTranspose = a_matrix; %Do not tranpose first matrix since the rows are passed through
% %Each column of the initial matrix is first isolated, diagonalized with the
% %correct number of zeroes, and accumulated/concatenated into a final matrix (a_signals)
% a_signals = zeros(size(a_matrixTranspose,1),2*length(a_matrixTranspose)-1); %Final zero matrix to accumulate all diagonalized matrices
% a_colTempAdj = []; %Adjusted Temporary Column Vector matrix i.e. diagonalized
% 
% %Iterate through each column to isolate columns (a_col)
% for m = 1:length(a_matrixTranspose)
%     a_col = diag(a_matrixTranspose(:,m)); %Diagonalizing the isolated column from original matrix
% 
%     %The final square matrix must be of size 2n-1, where n = size of the original matrix i.e., n x n matrix
%     %The required number of zero fill on either side of the matrix is
%     %dependent on its column index.
%     %All zero filled matrices must have same number of rows as initial
%     %matrix
%     %Number of columns (leftPad) = ColumnIndex - 1
%     %Number of columns (rightPad) = Size of original matrix - ColumnIndex 
%     %See notes below for explanation
%     requiredZeroFillLeft = zeros(size(a_matrixTranspose,1), m-1 );
%     requiredZeroFillRight = zeros(size(a_matrixTranspose,1), size(a_matrixTranspose,1)-m); %Zero filled matrix on right side of the matrix
% 
%     a_colTempAdj = cat(2, requiredZeroFillLeft, a_col, requiredZeroFillRight); %Concatenate zerofilled matrices to both ends of diagonalized matrix
%     a_signals = a_signals+a_colTempAdj; %Accumulate all adjusted diagonalized matrices
% end 
% tenFill = zeros(size(a_signals,1), 8-length(a_signals));
% a_signals = cat(2, a_signals, tenFill)
% 
% a1 = a_signals(1,:);
% a1_var.time = 0:1:length(a_signals)-1;
% a1_var.signals.values = a1';
% a1_var.signals.dimensions = 1;

% a2 = a_signals(2,:);
% a2_var.time = 0:1:length(a_signals)-1;
% a2_var.signals.values = a2';
% a2_var.signals.dimensions = 1;
% 
% a3 = a_signals(3,:);
% a3_var.time = 0:1:length(a_signals)-1;
% a3_var.signals.values = a3';
% a3_var.signals.dimensions = 1;
% 
% a4 = a_signals(4,:);
% a4_var.time = 0:1:length(a_signals)-1;
% a4_var.signals.values = a4';
% a4_var.signals.dimensions = 1;
