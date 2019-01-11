#pragma once
#include <string>
#include <iostream>
#include <list>
#include <cmath>
#include "Utilities.h"


enum Type {StartL, EndL, BranchL, RegularL };

struct Point
{
	float x;
	float y;
};
struct Segment
{
	Point start;
	Point end;
	int Type;
};


class L_System2D
{
public:
	L_System2D(std::string _Axiom, std::string _RuleX, std::string RuleF, int _MaxDepth, float _StartAngle, float _RuleAngle, float _Length);

	std::list<Segment> CreateSystem();
	
	
private:
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
	Point StartPosition{ 0.0, 0.0 };

	std::string CreateRules(std::string state, int depth);
	std::string CreatePoints(std::string rules, Point start, float Angle, float Length);

};

