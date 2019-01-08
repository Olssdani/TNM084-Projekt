#pragma once
#include "shader.h"
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include "Noise/noise1234.h"
#include <cmath>
#include <algorithm>  
#include <stdlib.h> 
#include <GLFW/glfw3.h>

#define SIZE 150
class Water
{
public:
	Water();
	~Water();
	void Render(glm::mat4 projection, glm::mat4 view);
	void UpdateShader();
	void WaterHeight(float a);

private:
	//Variables
	Shader * shader;
	unsigned int VBO, VAO, EBO;
	float ypos;

	void CreateMesh(float vert[], unsigned int ind[]);
};

