function [Result] = Lsystem3D(string, depth, maxDepth)
    Rule1 = 'FFF[+{&F0]FF[&{X]F0';
    Rule2 = '-&}FFX0'
    Rule3 = 'FF[+}XF0]'
    RuleF = 'FF';
    Result = '';
    if(depth == maxDepth) 
       Result =string;
       return;
    end
   
    depth = depth +1;
    
    for i=1:length(string)
        char = string(1,i);
        if(char == '[')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        elseif(char == ']')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth)) ;      
        elseif(char == 'X')
            r = rand();
            if(r <0.33)
                RuleX = Rule1;
            elseif(r<0.67)
                RuleX = Rule2;
            else
                RuleX = Rule3;
            end
            Result =strcat(Result,Lsystem3D(RuleX, depth, maxDepth));
        elseif(char == 'F')
            Result =strcat(Result,Lsystem3D(RuleF, depth, maxDepth));
        elseif(char == '-')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        elseif(char == '+')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        elseif(char == '&')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        elseif(char == '^')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        elseif(char == '}')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        elseif(char == '{')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        elseif(char == '|')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        elseif(char == '0')
            Result =strcat(Result,Lsystem3D(char, depth, maxDepth));
        end
    end
    
end

