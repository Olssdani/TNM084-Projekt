#pragma once
#include "Utilities.h"
#include <list>
#include <string>
#include <vector>
#include <iostream>


class L_System3D
{
public:
	L_System3D(std::string _Axiom, std::string _RuleX, std::string _Rule1, std::string _Rule2, std::string _Rule3, int _MaxDepth, glm::vec3 _StartDirection, float _RuleAngle, float _Length);
	~L_System3D();

	std::list<Segment3D> CreateSystem();

private:
	std::string RuleX;
	std::string RuleF;
	std::vector<std::string> Cases;
	std::string Rules;
	std::string Axiom;
	float StartLength;
	int MaxDepth;
	glm::vec3 StartDirection;
	float RuleAngle;
	glm::vec3 StartPosition = glm::vec3(0.0, 0.0, 0.0);
	std::list<Segment3D> Rsegments;
	glm::vec3 orto;

	std::string CreatePoints(std::string rules, glm::vec3 start, glm::vec3 Direction, glm::vec3 OrthoVec, float Length, float Width);
	std::string CreateRules(std::string state, int depth);
};

