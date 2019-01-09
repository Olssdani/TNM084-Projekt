% %%
% clc
% Axiom = '0';
% Startpos =[0,0];
% StartAngle = pi/2;
% Length = 1;
% n = 0;
% max = 5;
% figure();
% %axis([-5 5 -1 10])
% hold on
% string =Tree(Axiom,n, max);
% CreateStructure(string, Startpos, StartAngle, Length);

%%
clc
Axiom = 'X';
Startpos =[0,0];
StartAngle = pi/2-deg2rad(25);
Length = 1;
n = 0;
max = 6;
figure();
hold on
string =BarnsleyFern(Axiom,n, max);
CreateBarnsleyFern(string, Startpos, StartAngle, Length);









