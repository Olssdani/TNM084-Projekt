#pragma once
//Include all different things that might be needed
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <time.h>  
#include <stdlib.h> 
//Variable for Pi
#define M_PI 3.14159265358979323846  /* pi */
//Calculate radians to deegre and vice versa
#define D2R (M_PI*2)/360.0  /* Degree to radians */
#define R2D 360.0/(M_PI*2)  /* Radians to Degree */
//Struct to contain vertex
struct Vertex { glm::vec3 Position; };
//Segment type
enum Type { StartL, EndL, RegularL, BranchL};

//Segment in 2D
struct Segment
{
	glm::vec2 start;
	glm::vec2 end;
	int Type;
};

//Segment i 3D
struct Segment3D
{
	glm::vec3 Start;
	glm::vec3 End;
	Type type;
	glm::vec3 Direction;
	glm::vec3 Orto;
	float width;
	float length;

};