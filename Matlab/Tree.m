function [Result] = Tree(string,depth, maxDepth)
    Rule1 = '11';
    Rule0 = '1[0]0';
    Result = '';
    if(depth == maxDepth)
        
       Result =string;
       return;
    end
    
    
    depth = depth +1;
    for i=1:length(string)
        char = string(1,i)
        if(char == '[')
            Result =strcat(Result,Tree(char, depth, maxDepth))
        elseif(char == ']')
            Result =strcat(Result,Tree(char, depth, maxDepth))       
        elseif(char == '0')
            Result =strcat(Result,Tree(Rule0, depth, maxDepth))
        elseif(char == '1')
            Result =strcat(Result,Tree(Rule1, depth, maxDepth))
        end
    end
    
    
    
    
end

