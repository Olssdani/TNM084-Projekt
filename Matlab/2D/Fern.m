function [Result] = Fern(string,depth, maxDepth)
    %%RuleX = '[-X]FF-F-FX';
    %%RuleF = 'F';
%     RuleX = '[-X]FF-F-F';
%     RuleF = 'F';
    RuleX = '[-X]FFF-FF-F0';
    RuleF = 'F';
    Result = '';
    if(depth == maxDepth) 
       Result =string;
       return;
    end
    
    
    depth = depth +1;
    for i=1:length(string)
        char = string(1,i);
        if(char == '[')
            Result =strcat(Result,Fern(char, depth, maxDepth));
        elseif(char == ']')
            Result =strcat(Result,Fern(char, depth, maxDepth)) ;      
        elseif(char == 'X')
            Result =strcat(Result,Fern(RuleX, depth, maxDepth));
        elseif(char == 'F')
            Result =strcat(Result,Fern(RuleF, depth, maxDepth));
        elseif(char == '-')
            Result =strcat(Result,Fern(char, depth, maxDepth));
        elseif(char == '+')
            Result =strcat(Result,Fern(char, depth, maxDepth));      
        elseif(char == '0')
            Result =strcat(Result,Fern(char, depth, maxDepth));
        end
    end
    
end

