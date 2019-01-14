%%
clc
clear all
close all
Axiom = 'X';
Startpos =[0,0,0];
Direction = [0,1,0];
Length = 1;
n = 0;
max = 2;
figure();
axis([-25 25 -25 25 -25 25])
hold on
string =Lsystem3D(Axiom,n, max);
Create3D(string, Startpos, Direction, Length );