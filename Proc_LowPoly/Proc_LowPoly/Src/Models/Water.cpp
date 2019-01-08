#include "Water.h"



Water::Water()
{
	//The water height
	ypos = 0.0f;
	//Shader
	shader = new Shader("Shaders/WaterV.glsl", "Shaders/WaterF.glsl", "Shaders/WaterG.glsl");

	float vertices[3 * SIZE*SIZE]{ 0.0f };
	unsigned int indices[(SIZE - 1)*(SIZE - 1) * 3 * 2]{ 0.0f };
	CreateMesh(vertices, indices);

	// Create the buffers
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	//Bind the vertex buffer object
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Unbind the VAO
	glBindVertexArray(0);
}


Water::~Water()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
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
	glDrawElements(GL_TRIANGLES, (SIZE - 1)*(SIZE - 1) * 3 * 2, GL_UNSIGNED_INT, 0);

}
void Water::WaterHeight(float a)
{
	ypos += a;
}
void Water::CreateMesh(float vert[], unsigned int ind[])
{
	//Loop through the grid and creates a x and z position depending on a random function. Y position is depending in perlin noise
	for (int y = 0; y < SIZE; y++)
	{
		float j = (float)y / SIZE;
		for (int x = 0; x < SIZE; x++)
		{
			float i = (float)x / SIZE;
			vert[(x + y * SIZE) * 3] = ((float)x + 0.25 + (float)rand() / (2 * RAND_MAX));
			vert[(x + y * SIZE) * 3 + 1] = 0.0f;
			vert[(x + y * SIZE) * 3 + 2] = ((float)y + 0.25 + (float)rand() / (2 * RAND_MAX));
		}
	}
	//Create the triangles for each grid
	for (int y = 0; y < SIZE - 1; y++)
	{
		for (int x = 0; x < SIZE - 1; x++)
		{
			ind[(x + y * (SIZE - 1)) * 6 + 0] = x + y * (SIZE);
			ind[(x + y * (SIZE - 1)) * 6 + 1] = x + 1 + (y + 1) * (SIZE);
			ind[(x + y * (SIZE - 1)) * 6 + 2] = x + 1 + y * (SIZE);

			ind[(x + y * (SIZE - 1)) * 6 + 3] = x + y * (SIZE);
			ind[(x + y * (SIZE - 1)) * 6 + 4] = x + (y + 1) * (SIZE);
			ind[(x + y * (SIZE - 1)) * 6 + 5] = x + 1 + (y + 1) * (SIZE);
		}
	}
}

void Water::UpdateShader()
{
	glDeleteProgram(shader->ID);
	shader = new Shader("Shaders/WaterV.glsl", "Shaders/WaterF.glsl", "Shaders/WaterG.glsl");
}