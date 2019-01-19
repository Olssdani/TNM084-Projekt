#pragma once
#include <string>
#include <iostream>
#include <list>
#include <cmath>
#include "Utilities.h"

/*
	Class for generete the structure for a 2D plant
*/



class L_System2D
{
public:
	L_System2D(std::string _Axiom, std::string _RuleX, std::string RuleF, int _MaxDepth, float _StartAngle, float _RuleAngle, float _Length);

	//Create the system and return all segments
	std::list<Segment> CreateSystem();
	
	
private:
	//Variables
	std::string RuleX;
	std::string RuleF;
	std::string Rules;
	std::string Axiom;
	float StartLength;
	int MaxDepth;
	float StartAngle;
	float RuleAngle;
	static int Counter;
	std::list<Segment> Rsegments;
	glm::vec2 StartPosition{ 0.0, 0.0 };

	
	std::string CreateRules(std::string state, int depth);
	std::string CreatePoints(std::string rules, glm::vec2 start, float Angle, float Length);

};

