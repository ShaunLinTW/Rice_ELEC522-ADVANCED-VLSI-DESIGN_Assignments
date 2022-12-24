clear all;
clc;

testVectorLength = 41;

cordicMode = [1, 1];
fill = ones(size(cordicMode,1), testVectorLength-length(cordicMode));
cordicModeSignal = cat(2, cordicMode, fill);
cordicModeSignals = cordicModeSignal(1,:)
cordicModeSignals_var.time = 0:1:length(cordicModeSignal)-1;
cordicModeSignals_var.signals.values = cordicModeSignals';
cordicModeSignals_var.signals.dimensions = 1;

angleRadians = [0, 0];
fill = zeros(size(angleRadians,1), testVectorLength-length(angleRadians));
angleRadiansSignal = cat(2, angleRadians, fill);
angleRadiansSignals = angleRadiansSignal(1,:)
angleRadiansSignals_var.time = 0:1:length(angleRadiansSignal)-1;
angleRadiansSignals_var.signals.values = angleRadiansSignals';
angleRadiansSignals_var.signals.dimensions = 1;

xCartesian = [1, 1];
fill = ones(size(xCartesian,1), testVectorLength-length(xCartesian));
xCartesianSignal = cat(2, xCartesian, fill);
xCartesianSignals = xCartesianSignal(1,:)
xCartesianSignals_var.time = 0:1:length(xCartesianSignal)-1;
xCartesianSignals_var.signals.values = xCartesianSignals';
xCartesianSignals_var.signals.dimensions = 1;

yCartesian = 0:0.05:2;
fill = ones(size(yCartesian,1), testVectorLength-length(yCartesian));
yCartesianSignal = cat(2, yCartesian, fill);
yCartesianSignals = yCartesianSignal(1,:)
yCartesianSignals_var.time = 0:1:length(yCartesianSignal)-1;
yCartesianSignals_var.signals.values = yCartesianSignals';
yCartesianSignals_var.signals.dimensions = 1;
