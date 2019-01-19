#pragma once
#include "utilities.h"
#include "L-System/L_System3D.h"
#include <list>
#include <vector>
#include "shader.h"
#include <GLFW/glfw3.h>
#include "Stegu/TriangleSoup.h"
class Tree
{
public:
	Tree(int _Edges = 8, float _Thickness = 1.0);
	~Tree();
	void Render(glm::mat4 projection, glm::mat4 view);
	void UpdateShader();
	void SetTranslation(glm::vec3 t);
	void SetRotation(glm::vec3 r, float angle);
	void SetScale(glm::vec3 s);
	float y, x;
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
	TriangleSoup sphere;
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);
	std::list<Segment3D> ends;
	int indices_size;
	glm::mat4 S, T, R;
};
/*
#pragma once
#include "utilities.h"
#include "L-System/L_System3D.h"
#include <list>
#include <vector>
#include "shader.h"
#include <GLFW/glfw3.h>
#include "Stegu/TriangleSoup.h"

/*
	Class for generating trees

class Tree
{
public:
	//constructor
	Tree(int _Edges=8, float _Thickness =1.0);
	~Tree();
	//rendering function
	void Render(glm::mat4 projection, glm::mat4 view);
	//Update the shader
	void UpdateShader();
	//Set transformation matrix
	void SetTranslation(glm::vec3 t);
	void SetRotation(glm::vec3 r, float angle);
	void SetScale(glm::vec3 s);
	float y, x;
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
	TriangleSoup sphere;
	std::list<Segment3D> ends;
	glm::mat4 S, T, R;
	int indices_size;
	//Function
	void CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind);
};

*/