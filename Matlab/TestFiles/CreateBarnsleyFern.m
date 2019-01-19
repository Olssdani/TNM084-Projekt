function [ResultingString] = CreateBarnsleyFern(rules,Startpos, Angle, Length)
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
            rules =CreateBarnsleyFern(rules,Startpos, Angle, Length);  
        elseif(rules(1,i)==']')
            rules(1,i) = ' ';
            ResultingString = rules;
            return;
        end
        
        if(rules(1,i)=='-')
            Angle = Angle -deg2rad(25);
        elseif(rules(1,i)=='+')
            Angle = Angle +deg2rad(25);
        end
       
        rules(1,i) = ' ';
        Startpos = Endpos;
    end
end

