#include "L_System3D.h"


//Constructor
L_System3D::L_System3D(std::string _Axiom, std::string _Rule1, std::string _Rule2, std::string _Rule3, std::string _RuleF,int _MaxDepth, glm::vec3 _StartDirection, float _RuleAngle, float _Length)
{
	Cases.resize(3);
	//The three different rules
	Cases[0] = _Rule1;
	Cases[1] = _Rule2;
	Cases[2] = _Rule3;
	Axiom = _Axiom;
	RuleX = "";
	RuleF = _RuleF;
	StartLength = _Length;
	Rules = "";
	MaxDepth = _MaxDepth;
	StartDirection = _StartDirection;
	RuleAngle = _RuleAngle;
	orto = glm::vec3(1.0, 0.0, 0.0);
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
			//Random amogs the diffrent rules
			float r =((float)rand() / RAND_MAX);
			if (r < 0.33)
			{
				RuleX = Cases[0];
			}
			else if (r < 0.67)
			{
				RuleX = Cases[1];
			}
			else {
				RuleX = Cases[2];
			}
			Result = Result.append(CreateRules(RuleX, depth + 1));
		}
		state = state.substr(1, state.length());
	}
	return Result;
}

//Create the system and return the segments
std::list<Segment3D> L_System3D::CreateSystem() 
{
	Rules = CreateRules(Axiom, 0);
	CreatePoints(Rules, StartPosition, StartDirection, orto, StartLength, 1.0);
	return Rsegments;
}

std::string L_System3D::CreatePoints(std::string rules, glm::vec3 start, glm::vec3 Direction, glm::vec3 OrthoVec, float Length, float Width)
{
	// Set local vairables
	glm::vec3 End;
	Segment3D temp;
	bool first = true;
	
	//Loop until no more rules
	while (rules.length() > 0)
	{
		//Normalize the direction vectors just in case
		Direction = glm::normalize(Direction);
		OrthoVec = glm::normalize(OrthoVec);
		//Reset end point
		End.x = start.x;
		End.y = start.y;
		End.z = start.z;
		
		//Take one character from the rules
		std::string StateChar = rules.substr(0, 1);
		rules = rules.substr(1, rules.length());
		float angle = (20 + 20 * ((float)rand() / RAND_MAX))*D2R;
		if (StateChar == "X")
		{
			//Do nothing
		}
		else if (StateChar == "0")
		{
			//Set last segment to a end segment
			Rsegments.back().type = EndL;
		}
		else if (StateChar == "F")
		{
			//Go forward
			End = start+Length*Direction;
			if(first)
			{
				temp.type = StartL;
				first = false;
			}
			else {
				temp.type = RegularL;
			}
			
			temp.Start = start;
			temp.End = End;
			temp.Direction = Direction;
			temp.Orto = OrthoVec;
			temp.width = Width;
			temp.length = Length;
			Rsegments.push_back(temp);
			start = End;
		}
		else if (StateChar == "[")
		{
			//OPen new branch
			Rsegments.back().type = BranchL;
			//Recursive call and shorten the length and width
			rules = CreatePoints(rules, start, Direction, OrthoVec, Length*0.5, Width*0.5 );
		}
		else if (StateChar == "]")
		{
			//Close latest branch
			return rules;
		}
		else if (StateChar == "-")
		{
			//Rotate right on Y axis
			float angle = -360.0f*((float)rand() / RAND_MAX)*D2R;
			Direction = glm::rotateY(Direction,-angle );
			OrthoVec = glm::rotateY(OrthoVec, -angle);
		}
		else if (StateChar == "+")
		{
			//Rotate left on Y axis
			float angle = -360.0f*((float)rand() / RAND_MAX)*D2R;
			Direction = glm::rotateY(Direction, angle);
			OrthoVec = glm::rotateY(OrthoVec, angle);
		}
		else if (StateChar == "{")
		{
			//Rotate left on X axis
			
			Direction = glm::rotateX(Direction, angle);
			OrthoVec = glm::rotateX(OrthoVec, angle);
		}
		else if (StateChar == "}")
		{
			//Rotate right on X axis
			Direction = glm::rotateX(Direction, -angle);
			OrthoVec = glm::rotateX(OrthoVec, -angle);
		}
		else if (StateChar == "&")
		{
			//Rotate right on z axis
			Direction = glm::rotateZ(Direction, -angle);
			OrthoVec = glm::rotateZ(OrthoVec, -angle);
		}
		else if (StateChar == "^")
		{
			//Rotate left on Z axis
			Direction = glm::rotateZ(Direction, angle);
			OrthoVec = glm::rotateZ(OrthoVec, angle);
		}
		else if (StateChar == "|")
		{
			//For now do nothing, should rotate 180degree's and go backward
		}

	}
	return rules;
}

