clc; clear;

% [X,Y] = meshgrid(-pi:(2*pi)/100:pi,-1:2/5:1);
% Z = sin(X+Y);
% surf(X,Y,Z);

input = importdata('input_sample1.txt');
plot3(input(:,2),input(:,3),input(:,1),'o'); 