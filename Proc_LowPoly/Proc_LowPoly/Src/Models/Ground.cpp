#include "Ground.h"




Ground::Ground(int _GroundSize, int _VertexCount)
{
	//Shader
	shader = new Shader("Shaders/Ground/GroundV.glsl", "Shaders/Ground/GroundF.glsl", "Shaders/Ground/GroundG.glsl");
	
	//Set the noise
	GroundHeight = glm::vec2(10.0f, -10.0f);
	BigNoise = glm::vec3(0.0f, 0.0f, 0.0f);
	SmallNoise = glm::vec3(0.0f,0.0f,0.0f);
	GroundSmallHeight = 1.0f;

	//Size of grid and number of squares
	VertexCount = _VertexCount;
	GroundSize = _GroundSize;
	SquareSize = GroundSize / VertexCount;
	//Vertices and indices
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
	//glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),&indices[0], GL_STATIC_DRAW);

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

	shader->setVec3("BigNoise", BigNoise);
	shader->setVec3("SmallNoise", SmallNoise);
	shader->setVec2("GroundHeight", GroundHeight);
	shader->setFloat("GroundSize", GroundSize);
	shader->setFloat("SmallHeight", GroundSmallHeight);

	//Bind the VAO and draw the vertex
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 2*SIZE*SIZE);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}


void Ground::CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind)
{
	//Loop through the grid and creates a x and z position depending on a random function. Y position is depending in perlin noise
	Vertex temp;
	for (int y = 0; y < VertexCount; y++)
	{
		float j = (float)y / (VertexCount-1);
		for (int x = 0; x < VertexCount; x++)
		{
			float i = (float)x / (VertexCount-1);


			temp.Position.x = i * GroundSize  -SquareSize + SquareSize * (float)rand() / (2 * RAND_MAX);
			temp.Position.y = 0.0f; //std::max(2.0f, 40.0f * abs(noise3(20.0f*i, 50.0f*j, 0.5))) + 1.0f*noise3(20.0f*i, 15.0f*j, 0.5);
			temp.Position.z = j * GroundSize -SquareSize + SquareSize * (float)rand() / (2 * RAND_MAX);
			vert[x + y * VertexCount] = temp;
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
void Ground::UpdateShader()
{
	glDeleteProgram(shader->ID);
	shader = new Shader("Shaders/Ground/GroundV.glsl", "Shaders/Ground/GroundF.glsl", "Shaders/Ground/GroundG.glsl");
}

void Ground::SetGroundHeight(glm::vec2 Heights)
{
	GroundHeight.x += Heights.x;
	GroundHeight.y += Heights.y;
}
void Ground::SetMountainNoise(glm::vec3 Noise)
{
	BigNoise.x += Noise.x;
	BigNoise.y += Noise.y;
	BigNoise.z += Noise.z;
}
void Ground::SetGroundNoise(glm::vec3 Noise)
{
	SmallNoise.x += Noise.x;
	SmallNoise.y += Noise.y;
	SmallNoise.z += Noise.z;
}

void Ground::SetSmallHeight(float Heights)
{
	GroundSmallHeight += Heights;
	std::cout << GroundSmallHeight <<std::endl;

}