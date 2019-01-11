#pragma once
#include "shader.h"
#include "Noise/noise1234.h"
#include <cmath>
#include <algorithm>  
#include <stdlib.h> 
#include <vector>
#include "Utilities.h"

class Ground
{
public:
	Ground(int _GroundSize, int _VertexCount);
	~Ground();

	//Render the ground
	void Render(glm::mat4 projection, glm::mat4 view);
	void UpdateShader();
	//SetGroundHeight sets the max and min height that is possible. Max height might not be reach beacause of the noise that makes the height. 
	//The function raise the height by vec2(min, max);
	void SetGroundHeight(glm::vec2 Heights);
	//Set the noise that makes the mountain
	void SetMountainNoise(glm::vec3 Noise);
	//Set the noise that make small irragulirites in the ground
	void SetGroundNoise(glm::vec3 Noise);
	void SetSmallHeight(float Heights);

private:
	//Variables
	Shader *shader;
	unsigned int VBO, VAO, EBO;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	int GroundSize;
	int VertexCount;
	float SquareSize;
	glm::vec2 GroundHeight;
	float GroundSmallHeight;
	glm::vec3 BigNoise;
	glm::vec3 SmallNoise;

	//Functions
	//Creates the floor
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);
	
};

