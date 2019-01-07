#pragma once
#include "shader.h"
#include "Noise/noise1234.h"
#include <cmath>
#define SIZE 100
class Ground
{
public:
	Ground();
	~Ground();

	//Render the ground
	void Render(glm::mat4 projection, glm::mat4 view);

private:
	//Variables
	Shader *shader;
	unsigned int VBO, VAO, EBO;


	//Functions
	//Creates the floor
	void CreateGround(float vert[], unsigned int ind[]);
	
};

