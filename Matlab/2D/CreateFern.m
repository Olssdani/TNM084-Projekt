function [ResultingString] = CreateFern(rules,Startpos, Angle, Length)
    RuleAngle = deg2rad(20);
    for i = 1:length(rules)
        Endpos = Startpos;
        if(rules(1,i) == ' ')
           continue;
        end
        
        
        if(rules(1,i) == 'X')

        elseif(rules(1,i) == 'F')
            Endpos =[Startpos(1,1)+Length*cos(Angle),Startpos(1,2)+Length*sin(Angle)];
            X = linspace(Startpos(1,1),Endpos(1,1));
            Y = linspace(Startpos(1,2),Endpos(1,2));
            plot(X,Y);
        end
        
        if(rules(1,i)=='[')
            rules(1,i) = ' ';
            rules =CreateFern(rules,Startpos, Angle, Length);  
        elseif(rules(1,i)==']')
            rules(1,i) = ' ';
            ResultingString = rules;
            return;
        end
        
        if(rules(1,i)=='-')
            Angle = Angle -RuleAngle;
        elseif(rules(1,i)=='+')
            Angle = Angle +RuleAngle;
        end
       
        rules(1,i) = ' ';
        Startpos = Endpos
    end
end

