#pragma once
#include "L-System/L_System2D.h"
#include <string>
#include "shader.h"
#include <new>
#include "utilities.h"
#include <vector>
class Fern
{
public:
	Fern();
	~Fern();
	void Render(glm::mat4 projection, glm::mat4 view);
	void UpdateShader();
	

private:
	L_System2D *LSystem;
	//Variables
	Shader * shader;
	GLuint VBO[4], VAO[4], EBO[4];
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	std::list<Segment> Structure;
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);

};

