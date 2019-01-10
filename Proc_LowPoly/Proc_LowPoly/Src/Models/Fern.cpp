#include "Fern.h"



Fern::Fern()
{
	shader = new Shader("Shaders/Fern/FernV.glsl", "Shaders/Fern/FernF.glsl", "Shaders/Fern/FernG.glsl");
	LSystem = new L_System2D("X", "[-X]FFF-FF-F0", "F", 2, M_PI / 2.0f- 20.0f*D2R, 20.0f*D2R, 1.0f);
	Structure = LSystem->CreateSystem();
	
	vertices.resize((Structure.size()+2)*3+1);
	indices.resize(Structure.size()*4*3);
	CreateMesh(vertices, indices);

	for each (Vertex var in vertices)
	{
		std::cout << var.Position.x << " " << var.Position.y << " " << var.Position.z << std::endl;
	}
	std::cout << std::endl;
	for (int i = 0; i < indices.size(); i = i+3)
	{
		std::cout << indices[i] << " " << indices[i + 1] << " " << indices[i + 2] << std::endl;
	}

	// Create the buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind the vertex buffer object
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Unbind the VAO
	glBindVertexArray(0);

}

void Fern::CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind)
{
	Vertex temp;
	int counter = 0;
	float down = 0.3;
	
	//Left Start vertex
	temp.Position.x = 0;
	temp.Position.y = -down;
	temp.Position.z = -0.2f;
	vert[counter] = temp;
	counter++;

	//Middle vertex
	temp.Position.x = 0;
	temp.Position.y = -down;
	temp.Position.z = 0;
	vert[counter] = temp;
	counter++;

	//Right vertex
	temp.Position.x = 0;
	temp.Position.y = -down;
	temp.Position.z = 0.2f;
	vert[counter] = temp;
	counter++;

	for each (Segment seg in Structure)
	{
		//Left vertex
		temp.Position.x = seg.end.x;
		temp.Position.y = seg.end.y- down;
		temp.Position.z = -1.0f;
		vert[counter] = temp;
		counter++;

		//Middle vertex
		temp.Position.x = seg.end.x;
		temp.Position.y = seg.end.y;
		temp.Position.z = 0;
		vert[counter] = temp;
		counter++;

		//Right vertex
		temp.Position.x = seg.end.x;
		temp.Position.y = seg.end.y- down;
		temp.Position.z = 1.0f;
		vert[counter] = temp;
		counter++;
	}
	counter = 5;
	
	for(int i =0; i <Structure.size()*2*6;i = i+12)
	{
		
		if (i!=0 &&abs((double)(Structure.size() * 2 * 6) / (i) -2)<0.0001)
		{
			ind[i] = 0;
			ind[i + 1] = counter - 1;
			ind[i + 2] = counter - 2;

			ind[i + 3] = 0;
			ind[i + 4] = 1;
			ind[i + 5] = counter - 1;

			ind[i + 6] = counter - 1;
			ind[i + 7] = 1;
			ind[i + 8] = 2;

			ind[i + 9] = counter - 1;
			ind[i + 10] = 2;
			ind[i + 11] = counter;

		}
		else {
			ind[i] = counter - 5;
			ind[i + 1] = counter - 1;
			ind[i + 2] = counter - 2;

			ind[i + 3] = counter - 5;
			ind[i + 4] = counter - 4;
			ind[i + 5] = counter - 1;

			ind[i + 6] = counter - 1;
			ind[i + 7] = counter - 4;
			ind[i + 8] = counter - 3;

			ind[i + 9] = counter - 1;
			ind[i + 10] = counter - 3;
			ind[i + 11] = counter;
			
		}
		counter = counter + 3;
	}

}
void Fern::UpdateShader()
{
	glDeleteProgram(shader->ID);
	shader = new Shader("Shaders/Fern/FernV.glsl", "Shaders/Fern/FernF.glsl", "Shaders/Fern/FernG.glsl");
}

void Fern::Render(glm::mat4 projection, glm::mat4 view)
{
	//Start shader
	shader->use();

	//Send variables to shader
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	glm::mat4 model = glm::translate(glm::vec3(30.0,50.0,30.0));
	shader->setMat4("model", model);

	//Bind the VAO and draw the vertex
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 2*SIZE*SIZE);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}
Fern::~Fern()
{
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
