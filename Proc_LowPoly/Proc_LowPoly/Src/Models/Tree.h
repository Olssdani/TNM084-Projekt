#pragma once
#include "utilities.h"
#include "L-System/L_System3D.h"
#include <list>
#include <vector>
#include "shader.h"
#include <GLFW/glfw3.h>
class Tree
{
public:
	Tree(int _Edges, float _Thickness);
	~Tree();
	void Render(glm::mat4 projection, glm::mat4 view);
	void UpdateShader();

private:
	L_System3D * LSystem;
	//Variables
	Shader * shader;
	GLuint VBO, VAO, EBO;
	int Edges;
	float Thickness;
	std::vector<unsigned int> indices;
	std::vector<Vertex> vertices;
	std::list<Segment3D> Structure;
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);
};

