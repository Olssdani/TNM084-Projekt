%%
clc
Axiom = 'X';
Startpos =[0,0];
StartAngle = pi/2-deg2rad(20);
Length = 1;
n = 0;
max = 2;
figure();
axis([-0 15 0 15])
hold on
string =Fern(Axiom,n, max);
CreateFern(string, Startpos, StartAngle, Length);


