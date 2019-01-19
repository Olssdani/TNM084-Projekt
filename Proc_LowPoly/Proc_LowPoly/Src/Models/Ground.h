#pragma once
#include "shader.h"
#include "Noise/noise1234.h"
#include <cmath>
#include <algorithm>  
#include <stdlib.h> 
#include <vector>
#include "Utilities.h"
/*
	Class for generating the ground
*/
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

	//Render the height data
	void RenderHeight(unsigned int &SCR_WIDTH, unsigned int &SCR_HEIGHT);
	//Data for height
	float data[150 * 150];
	float max;
private:
	//Variables
	Shader *shader, *shaderH;
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
	//Creates the ground
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);
	
};

