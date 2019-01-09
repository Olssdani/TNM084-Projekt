function [Result] = BarnsleyFern(string,depth, maxDepth)
    RuleX = 'F+[[X]-X]-F[-FX]+X';
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
            Result =strcat(Result,BarnsleyFern(char, depth, maxDepth));
        elseif(char == ']')
            Result =strcat(Result,BarnsleyFern(char, depth, maxDepth)) ;      
        elseif(char == 'X')
            Result =strcat(Result,BarnsleyFern(RuleX, depth, maxDepth));
        elseif(char == 'F')
            Result =strcat(Result,BarnsleyFern(RuleF, depth, maxDepth));
        elseif(char == '-')
            Result =strcat(Result,BarnsleyFern(char, depth, maxDepth));
        elseif(char == '+')
            Result =strcat(Result,BarnsleyFern(char, depth, maxDepth));
        end
    end
    
end

