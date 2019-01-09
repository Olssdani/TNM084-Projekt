function [ResultingString] = CreateStructure(rules,Startpos, Angle, Length)
    

    for i = 1:length(rules)
        Endpos = Startpos;
        if(rules(1,i) == ' ')
           continue;
        end
        
        
        if(rules(1,i) == '1')
            Endpos =[Startpos(1,1)+cos(Angle)*Length,Startpos(1,2)+Length*sin(Angle)];
            X = linspace(Startpos(1,1),Endpos(1,1));
            Y = linspace(Startpos(1,2),Endpos(1,2));
            plot(X,Y)
        elseif(rules(1,i) == '0')
            Endpos =[Startpos(1,1)+Length*cos(Angle),Startpos(1,2)+Length*sin(Angle)];
            X = linspace(Startpos(1,1),Endpos(1,1));
            Y = linspace(Startpos(1,2),Endpos(1,2));
            plot(X,Y);
            rules(1,i) = ' ';
            ResultingString = rules;
            return
        end
        
        if(rules(1,i)=='[')
            rules(1,i) = ' ';
            rules =CreateStructure(rules,Startpos, Angle+pi/4, Length);  
        elseif(rules(1,i)==']')
            Angle = Angle -pi/4;
            
        end
       
        rules(1,i) = ' ';
        Startpos = Endpos;
    end



%extractAfter(str,6)
    
end

