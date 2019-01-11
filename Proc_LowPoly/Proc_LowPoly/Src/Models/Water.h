#pragma once
#include "shader.h"

#include "Noise/noise1234.h"
#include <cmath>
#include <algorithm>  
#include <stdlib.h> 
#include <GLFW/glfw3.h>
#include <vector>
#include "Utilities.h"



class Water
{
public:
	Water(unsigned int WaterSize, unsigned int VertexCount);
	~Water();
	void Render(glm::mat4 projection, glm::mat4 view);
	void UpdateShader();
	void WaterHeight(float a);

private:
	//Variables
	Shader * shader;
	unsigned int VBO, VAO, EBO;
	float ypos;
	unsigned int WaterSize;
	unsigned int VertexCount;
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	void CreateMesh(float vert[], unsigned int ind[]);
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);
};

