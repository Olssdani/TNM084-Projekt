#include "Water.h"



Water::Water(unsigned int _WaterSize, unsigned int _VertexCount)
{
	//The water height
	ypos = -5.0f;
	//Shader
	shader = new Shader("Shaders/Water/WaterV.glsl", "Shaders/Water/WaterF.glsl", "Shaders/Water/WaterG.glsl");
	WaterSize = _WaterSize;
	VertexCount = _VertexCount;


	vertices.resize(VertexCount*VertexCount);
	indices.resize((VertexCount - 1)*(VertexCount - 1) * 3 * 2);
	CreateMesh(vertices, indices);

	// Create the buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind the vertex buffer object
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
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


Water::~Water()
{
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	indices.clear();
	vertices.clear();
}

void Water::Render(glm::mat4 projection, glm::mat4 view)
{
	//Start shader
	shader->use();

	//Send variables to shader
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	glm::mat4 model = glm::translate(glm::vec3(0.0, ypos, 0.0));
	shader->setMat4("model", model);
	shader->setFloat("Time", glfwGetTime());


	//Bind the VAO and draw the vertex
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 2*SIZE*SIZE);
	glDrawElements(GL_TRIANGLES,indices.size(), GL_UNSIGNED_INT, 0);


}
void Water::WaterHeight(float a)
{
	ypos += a;
	std::cout << ypos << std::endl;
}

void Water::CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind)
{
	Vertex temp;
	//Loop through the grid and creates a x and z position depending on a random function. Y position is depending in perlin noise
	for (int y = 0; y < VertexCount; y++)
	{
		float j = (float)y / (VertexCount-1);
		for (int x = 0; x < VertexCount; x++)
		{
			float i = (float)x / (VertexCount-1);
			temp.Position.x = i * WaterSize; // +0.25 + (float)rand() / (2 * RAND_MAX));
			temp.Position.y = 0.0f;
			temp.Position.z = j * WaterSize;// + 0.25 + (float)rand() / (2 * RAND_MAX));
			vert[(x + y * VertexCount)] =temp;
		}
	}
	//Create the triangles for each grid
	for (int y = 0; y < VertexCount - 1; y++)
	{
		for (int x = 0; x < VertexCount - 1; x++)
		{
			ind[(x + y * (VertexCount - 1)) * 6 + 0] = x + y * (VertexCount);
			ind[(x + y * (VertexCount - 1)) * 6 + 1] = x + 1 + (y + 1) * (VertexCount);
			ind[(x + y * (VertexCount - 1)) * 6 + 2] = x + 1 + y * (VertexCount);

			ind[(x + y * (VertexCount - 1)) * 6 + 3] = x + y * (VertexCount);
			ind[(x + y * (VertexCount - 1)) * 6 + 4] = x + (y + 1) * (VertexCount);
			ind[(x + y * (VertexCount - 1)) * 6 + 5] = x + 1 + (y + 1) * (VertexCount);
		}
	}
}

void Water::UpdateShader()
{
	glDeleteProgram(shader->ID);
	shader = new Shader("Shaders/Water/WaterV.glsl", "Shaders/Water/WaterF.glsl", "Shaders/Water/WaterG.glsl");
}