#include "L_System3D.h"



L_System3D::L_System3D(std::string _Axiom, std::string _RuleX, std::string _RuleF, int _MaxDepth, glm::vec3 _StartDirection, float _RuleAngle, float _Length)
{

	Axiom = _Axiom;
	RuleX = _RuleX;
	RuleF = _RuleF;
	StartLength = _Length;
	Rules = "";
	MaxDepth = _MaxDepth;
	StartDirection = _StartDirection;
	RuleAngle = _RuleAngle;
}


L_System3D::~L_System3D()
{
}

std::string L_System3D::CreateRules(std::string state, int depth)
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
	while (state.length()>0)
	{
		//Get just one character in a substring
		std::string StateChar = state.substr(0, 1);

		//Check which charachter and do accordling to the rules
		if (StateChar == "[")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "]")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "-")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "+")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "|")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "}")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "{")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "&")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "^")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "0")
		{
			Result = Result.append(StateChar);
		}
		else if (StateChar == "F")
		{
			Result = Result.append(CreateRules(RuleF, depth + 1));
		}
		else if (StateChar == "X")
		{
			Result = Result.append(CreateRules(RuleX, depth + 1));
		}
		state = state.substr(1, state.length());
	}
	return Result;
}

void L_System3D::CreateSystem() //std::list<Segment>
{
	Rules = CreateRules(Axiom, 0);
	std::cout << Rules << std::endl;
	CreatePoints(Rules, StartPosition, StartDirection, StartLength);

	for each (Segment3D seg in Rsegments)
	{
		std::cout <<"Start: " << seg.Start.x   << " " << seg.Start.y << " " << seg.Start.z  << " End: " <<seg.End.x << " " << seg.End.y << " " << seg.End.z<<  "type: " << seg.type << std::endl;
	}
//	return Rsegments;
}

std::string L_System3D::CreatePoints(std::string rules, glm::vec3 start, glm::vec3 Direction, float Length)
{
	glm::vec3 End;
	Segment3D temp;
	//Loop until no more rules
	while (rules.length() > 0)
	{
		//Reset end point
		End.x = start.x;
		End.y = start.y;
		End.z = start.z;
		//Take one character from the rules
		std::string StateChar = rules.substr(0, 1);
		rules = rules.substr(1, rules.length());

		if (StateChar == "X")
		{
			//Do nothing
		}
		else if (StateChar == "0")
		{
			Rsegments.back().type = EndL;
		}
		else if (StateChar == "F")
		{
			//model = glm::rotate(model, angle, glm::vec3(0.0, 1.0, 0.0));
			End = start+Length*Direction;
			
			temp.type = RegularL;
			temp.Start = start;
			temp.End = End;
			Rsegments.push_back(temp);
			start = End;
		}
		else if (StateChar == "[")
		{
			rules = CreatePoints(rules, start, Direction, Length);
		}
		else if (StateChar == "]")
		{
			return rules;
		}
		else if (StateChar == "-")
		{
			Direction = glm::rotateY(Direction, -RuleAngle);
		}
		else if (StateChar == "+")
		{
			Direction = glm::rotateY(Direction, RuleAngle);
		}
		else if (StateChar == "{")
		{
			Direction = glm::rotateX(Direction, RuleAngle);
		}
		else if (StateChar == "}")
		{
			Direction = glm::rotateX(Direction, -RuleAngle);
		}
		else if (StateChar == "&")
		{
			Direction = glm::rotateZ(Direction, -RuleAngle);
		}
		else if (StateChar == "^")
		{
			Direction = glm::rotateZ(Direction, RuleAngle);
		}
		else if (StateChar == "|")
		{
			
		}

	}
	return rules;
}