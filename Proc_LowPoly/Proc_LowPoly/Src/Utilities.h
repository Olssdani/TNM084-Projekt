#pragma once
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <time.h>  
#include <stdlib.h> 
#define M_PI 3.14159265358979323846  /* pi */
#define D2R (M_PI*2)/360.0  /* Degree to radians */
#define R2D 360.0/(M_PI*2)  /* Radians to Degree */
struct Vertex { glm::vec3 Position; };
enum Type { StartL, EndL, RegularL, BranchL};
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

struct Segment3D
{
	glm::vec3 Start;
	glm::vec3 End;
	Type type;
	glm::vec3 Direction;
	glm::vec3 Orto;

};