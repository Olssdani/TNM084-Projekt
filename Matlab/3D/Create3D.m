function [ResultingString] = Create3D(rules, Startpos, Direction, Length)
    Angle = 45;
    %Normalize direction just in case
    Direction =  Direction/norm(Direction);
    %Loop for length of rules
    for i = 1:length(rules)
        %Set end pos if no rotation is made
        Endpos = Startpos;
        %Just because bad implementation
        if(rules(1,i) == ' ')
           continue;
        end
        
       
        if(rules(1,i) == 'X')
         %Do notihing
        
        elseif(rules(1,i) == 'F')           
            %go forward 
            Endpos = Startpos+Direction*Length;
            X = linspace(Startpos(1,1),Endpos(1,1));
            Y = linspace(Startpos(1,2),Endpos(1,2));
            Z = linspace(Startpos(1,3),Endpos(1,3));
            plot3(X,Y,Z);
        end
        
        if(rules(1,i)=='[')
            rules(1,i) = ' ';
            rules =Create3D(rules,Startpos, Direction, Length);  
        elseif(rules(1,i)==']')
            rules(1,i) = ' ';
            ResultingString = rules;
            return;
        end
        
        if(rules(1,i)=='-')
            Direction = Direction*roty(-Angle)
        elseif(rules(1,i)=='+')
            Direction = Direction*roty(Angle)
        elseif(rules(1,i)=='&')
            Direction = Direction*rotz(-Angle)
        elseif(rules(1,i)=='^')
            Direction = Direction*rotz(Angle)   
        elseif(rules(1,i)=='}')
            Direction = Direction*rotx(-Angle)
        elseif(rules(1,i)=='{')
            Direction = Direction*rotx(Angle)
        elseif(rules(1,i)=='|')
            %Direction = Direction*rotx(-Angle)    
        end
       
        rules(1,i) = ' ';
        Startpos = Endpos;
    end
end

