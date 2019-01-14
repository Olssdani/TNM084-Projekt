function [Result] = Lsystem3D(string, depth, maxDepth)
    RuleX = 'FFF[+{&FFX0]FFF0';
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

