#pragma once
#include "L-System/L_System2D.h"
#include <string>
#include "shader.h"
#include <new>
#include "utilities.h"
#include <vector>
/*
	This is the class for creating grass, however was the plan to make a fern first but
	I changed that and didn't care to change the name

*/
class Fern
{
public:
	Fern();
	~Fern();
	//Render function
	void Render(glm::mat4 projection, glm::mat4 view);
	//Update shader
	void UpdateShader();
	//Set different transformation matrix
	void SetTranslation(glm::vec3 t);
	void SetRotation(glm::vec3 r, float angle);
	void SetScale(glm::vec3 s);

private:
	//L-system
	L_System2D *LSystem;
	//Variables
	Shader * shader;
	GLuint VBO[4], VAO[4], EBO[4];
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	std::list<Segment> Structure;
	glm::mat4 S, T, R;
	int IndicesSize;
	//Crete the msh
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);

};

