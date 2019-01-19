#include "L_System2D.h"


//Constructor
L_System2D::L_System2D(std::string _Axiom, std::string _RuleX, std::string _RuleF, int _MaxDepth, float _StartAngle, float _RuleAngle, float _Length)
{
	

	Axiom = _Axiom;
	RuleX = _RuleX;
	RuleF = _RuleF;
	StartLength = _Length;
	Rules = "";
	MaxDepth = _MaxDepth;
	StartAngle = _StartAngle;
	RuleAngle = _RuleAngle;

}

//Create the rules
std::string L_System2D::CreateRules(std::string state, int depth)
{
	//Resulting string with rule
	std::string Result = "";

	// MaxDepth is reach end and return the string state
	if (depth == MaxDepth)
	{
		Result = state;
		return Result;
	}
	
	//Loop thorugh all the characters in state
	while(state.length()>0)
	{
		//Get just one character in a substring
		std::string StateChar = state.substr(0,1);

		//Check which charachter and do accordling to the rules
		if (StateChar == "[")
		{
			Result = Result.append(StateChar);
		}else if (StateChar == "]")
		{
			Result = Result.append(StateChar);
		}else if (StateChar == "-")
		{
			Result = Result.append(StateChar);
		}else if (StateChar == "+")
		{
			Result = Result.append(StateChar);
		}else if (StateChar == "0")
		{
			Result = Result.append(StateChar);
		}else if (StateChar == "F")
		{
			Result = Result.append(CreateRules(RuleF, depth+1));
		}else if (StateChar == "X")
		{
			Result = Result.append(CreateRules(RuleX, depth+1));
		}
		state = state.substr(1, state.length());
	}
	return Result;
}

std::list<Segment> L_System2D::CreateSystem()
{
	Rules = CreateRules(Axiom, 0);
	CreatePoints(Rules,StartPosition, StartAngle, StartLength);
	return Rsegments;


}

std::string L_System2D::CreatePoints(std::string rules, glm::vec2 start, float Angle, float Length)
{
	glm::vec2 End;
	Segment temp;
	//Loop until no more rules
	while (rules.length() > 0)
	{

		float alpha = RuleAngle- 20.0f * D2R + 40.0f * ((float)rand() / RAND_MAX)*D2R;
		//Reset end point
		End.x = start.x;
		End.y = start.y;
		//Take one character from the rules
		std::string StateChar = rules.substr(0, 1);
		rules = rules.substr(1, rules.length());
		
		if (StateChar == "X")
		{
			//Do nothing
		}
		else if (StateChar == "0")
		{
			Rsegments.back().Type = EndL;
		}
		else if (StateChar == "F")
		{
			//End pos = start pos + the length*unit circle
			End.x = start.x + Length * cos(Angle);
			End.y = start.y + Length * sin(Angle);
			temp.start = start;
			temp.end = End;
			temp.Type = RegularL;
			Rsegments.push_back(temp);
			//Set the start to the end
			start.x = End.x;
			start.y = End.y;

		}
		else if (StateChar == "[")
		{
			//recursive call
			rules = CreatePoints(rules, start, Angle, Length);
		}
		else if (StateChar == "]")
		{
			//Go back
			return rules;
		}
		else if (StateChar == "-")
		{
			Angle = Angle - alpha;
		}
		else if (StateChar == "+")
		{
			Angle = Angle + alpha;
		}

	}
	return rules;
}