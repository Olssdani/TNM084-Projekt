#include "Ground.h"




Ground::Ground()
{
	//Shader
	shader = new Shader("Shaders/Vertex.glsl", "Shaders/Fragment.glsl");

	//float vertices[12]{
	//	// positions         // colors
	//	-5.0f, 0.0f, -5.0f,   // bottom right
	//	-5.0f, 0.0f, 5.0f,  // bottom left
	//	5.0f,  0.0f, 5.0f, 
	//	 5.0f, 0.0f, -5.0f,  // bottom right
	//// top 
	//};

	//unsigned int indices[6]{ 0,1,2,0,2,3 };

	float vertices[3 * SIZE*SIZE]{ 0.0f };
	unsigned int indices[(SIZE-1)*(SIZE-1)*3*2]{0.0f};
	CreateGround(vertices, indices);


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


Ground::~Ground()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

//Render
void Ground::Render(glm::mat4 projection, glm::mat4 view)
{
	//Start shader
	shader->use();

	//Send variables to shader
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	glm::mat4 model = glm::mat4(1.0f);
	shader->setMat4("model", model);

	//Bind the VAO and draw the vertex
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 2*SIZE*SIZE);
	glDrawElements(GL_TRIANGLES, (SIZE - 1)*(SIZE - 1) * 3 * 2, GL_UNSIGNED_INT, 0);

}


void Ground::CreateGround(float vert[], unsigned int ind[])
{




	for (int y = 0; y < SIZE;y++)
	{
		for (int x = 0; x < SIZE; x++)
		{
			vert[(x + y * SIZE) * 3] = (float)x;
			vert[(x + y * SIZE) * 3 + 1] = 0.0f;
			vert[(x + y * SIZE) * 3 + 2] = (float)y;
		}
	}
	for (int i = 0; i < 3 * SIZE*SIZE; i = i+3)
	{
		std::cout << vert[i] << " " << vert[i+1] << " " << vert[i+2] << std::endl;
	}
	std::cout << std::endl;
	int counter = 0;
	for (int y = 0; y < SIZE-1; y++)
	{
		for (int x = 0; x < SIZE-1; x++)
		{
			ind[(x + y*(SIZE - 1)) * 6 + 0] = x + y * (SIZE);
			ind[(x + y*(SIZE - 1)) * 6 + 1] = x + 1 + (y + 1) * (SIZE);
			ind[(x + y*(SIZE - 1)) * 6 + 2] = x + 1+ y * (SIZE);

			ind[(x + y * (SIZE - 1)) * 6 + 3] = x + y * (SIZE);
			ind[(x + y * (SIZE - 1)) * 6 + 4] = x + (y+1) * (SIZE);
			ind[(x + y * (SIZE - 1)) * 6 + 5] = x + 1 + (y+1) * (SIZE);
			
		}
	}

	std::cout << "Indices" << std::endl;
	for (int i = 0; i < ((SIZE - 1)*(SIZE - 1))*3*2; i = i + 3)
	{
		std::cout << ind[i] << " " << ind[i + 1] << " " << ind[i + 2] << std::endl;
	}
}