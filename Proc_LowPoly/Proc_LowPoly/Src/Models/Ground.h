#pragma once
#include "shader.h"
#include "Noise/noise1234.h"
#include <cmath>
#include <algorithm>  
#include <stdlib.h> 
#include <vector>
#include "Utilities.h"
//Dies when set to 200, need do figure that shit out
#define SIZE 150

class Ground
{
public:
	Ground();
	~Ground();

	//Render the ground
	void Render(glm::mat4 projection, glm::mat4 view);
	void UpdateShader();

private:
	//Variables
	Shader *shader;
	unsigned int VBO, VAO, EBO;
	std::vector<Vertex> vertices;

	//Functions
	//Creates the floor
	void CreateGround(float vert[], unsigned int ind[]);
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);
	
};

