#include "Fern.h"



Fern::Fern()
{
	shader = new Shader("Shaders/Fern/FernV.glsl", "Shaders/Fern/FernF.glsl", "Shaders/Fern/FernG.glsl");
	LSystem = new L_System2D("X", "[-X]FFF-FF-F0", "F", 2, M_PI / 2.0f- 20.0f*D2R, 20.0f*D2R, 1.0f);
	Structure = LSystem->CreateSystem();
	
	//vertices.resize((Structure.size()+2)*3+1);
	//indices.resize(Structure.size()*4*3);
	vertices.resize((Structure.size()*4+4)*3);
	indices.resize(Structure.size()*4*3*2);
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
	temp.Position.z = -0.5f;
	vert[counter] = temp;
	counter++;

	//Middle Top vertex
	temp.Position.x = 0;
	temp.Position.y = -down;
	temp.Position.z = 0;
	vert[counter] = temp;
	counter++;

	//Middle Top vertex
	temp.Position.x = 0;
	temp.Position.y = -down;
	temp.Position.z = 0;
	vert[counter] = temp;
	counter++;

	//Right vertex
	temp.Position.x = 0;
	temp.Position.y = -down;
	temp.Position.z = 0.5f;
	vert[counter] = temp;
	counter++;

	for each (Segment seg in Structure)
	{
		float width;
		float height;
		float depth;
		float lower;
		//float 
		if (seg.Type == EndL)
		{
			width = 0.0f;
			height = seg.end.y;
			depth = seg.end.x;
			lower = 0.0f;
		}
		else if (seg.Type == RegularL)
		{
			width = 0.7;
			height = seg.end.y;
			depth = seg.end.x;
			lower = down;

		}
		//Left vertex
		temp.Position.x = depth;
		temp.Position.y = height - lower;
		temp.Position.z = -width;
		vert[counter] = temp;
		counter++;

		//Middle Top vertex
		temp.Position.x = depth;
		temp.Position.y = height;
		temp.Position.z = 0;
		vert[counter] = temp;
		counter++;

		//Middle bot vertex
		temp.Position.x = depth;
		temp.Position.y = height;
		temp.Position.z = 0;
		vert[counter] = temp;
		counter++;

		//Right vertex
		temp.Position.x = depth;
		temp.Position.y = height - lower;
		temp.Position.z = width;
		vert[counter] = temp;
		counter++;
	}
	counter = 7;

	for (int i = 0; i <Structure.size()*8*3; i = i + 24)
	{

		if (i != 0 && abs((double)(Structure.size() * 8 * 3) / (i)-2)<0.0001)
		{
			//Top
			ind[i] = 0;
			ind[i + 1] = 1;
			ind[i + 2] = counter - 2;

			ind[i + 3] = 0;
			ind[i + 4] = counter - 2;
			ind[i + 5] = counter - 3;

			ind[i + 6] = 1;
			ind[i + 7] = 3;
			ind[i + 8] = counter - 2;

			ind[i + 9] = 3;
			ind[i + 10] = counter;
			ind[i + 11] = counter - 2;

			//Bot
			ind[i + 12] = 0;
			ind[i + 13] = counter - 1;
			ind[i + 14] = 2;

			ind[i + 15] = 0;
			ind[i + 16] = counter - 3;
			ind[i + 17] = counter - 1;

			ind[i + 18] = 2;
			ind[i + 19] = counter - 1;
			ind[i + 20] = 3;

			ind[i + 21] = counter - 1;
			ind[i + 22] = counter;
			ind[i + 23] = 3;

		}
		else {
			//Top
			ind[i] = counter - 7;
			ind[i + 1] = counter - 6;
			ind[i + 2] = counter - 2;

			ind[i + 3] = counter - 7;
			ind[i + 4] = counter - 2;
			ind[i + 5] = counter - 3;

			ind[i + 6] = counter - 6;
			ind[i + 7] = counter - 4;
			ind[i + 8] = counter - 2;

			ind[i + 9] = counter - 4;
			ind[i + 10] = counter;
			ind[i + 11] = counter - 2;

			//Bot
			ind[i + 12] = counter - 7;
			ind[i + 13] = counter - 1;
			ind[i + 14] = counter - 5;

			ind[i + 15] = counter - 7;
			ind[i + 16] = counter - 3;
			ind[i + 17] = counter - 1;

			ind[i + 18] = counter - 5;
			ind[i + 19] = counter - 1;
			ind[i + 20] = counter - 4;

			ind[i + 21] = counter - 1;
			ind[i + 22] = counter;
			ind[i + 23] = counter - 4;

		}
		counter = counter + 4;
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

	for (int i = 0; i < 360; i = i + 90)
	{
		float angle = (float)i*D2R;
		glm::mat4 translate = glm::translate(glm::vec3(0.5, 0.0, 0.0));
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, angle, glm::vec3(0.0, 1.0, 0.0) );
		model = model *translate;
		shader->setMat4("model", model);

		//Bind the VAO and draw the vertex
		glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 2*SIZE*SIZE);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	}
	

}
Fern::~Fern()
{
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}




//Vertex temp;
//int counter = 0;
//float down = 0.3;
//
////Left Start vertex
//temp.Position.x = 0;
//temp.Position.y = -down;
//temp.Position.z = -0.2f;
//vert[counter] = temp;
//counter++;

////Middle vertex
//temp.Position.x = 0;
//temp.Position.y = -down;
//temp.Position.z = 0;
//vert[counter] = temp;
//counter++;

////Right vertex
//temp.Position.x = 0;
//temp.Position.y = -down;
//temp.Position.z = 0.2f;
//vert[counter] = temp;
//counter++;
//
//for each (Segment seg in Structure)
//{
//	float width;
//	float height;
//	float depth;
//	//float 
//	if (seg.Type == EndL)
//	{
//		width = 0.0f;
//		height = seg.end.y;
//		depth = seg.end.x;
//	}
//	else if (seg.Type == RegularL)
//	{
//		width = 1.0;
//		height = seg.end.y;
//		depth = seg.end.x;
//	}
//	//Left vertex
//	temp.Position.x = depth;
//	temp.Position.y = height - down;
//	temp.Position.z = -width;
//	vert[counter] = temp;
//	counter++;

//	//Middle vertex
//	temp.Position.x = depth;
//	temp.Position.y = height;
//	temp.Position.z = 0;
//	vert[counter] = temp;
//	counter++;

//	//Right vertex
//	temp.Position.x = depth;
//	temp.Position.y = height - down;
//	temp.Position.z = width;
//	vert[counter] = temp;
//	counter++;
//}
//counter = 5;
//
//for(int i =0; i <Structure.size()*2*6;i = i+12)
//{
//	
//	if (i!=0 &&abs((double)(Structure.size() * 2 * 6) / (i) -2)<0.0001)
//	{
//		ind[i] = 0;
//		ind[i + 1] = counter - 1;
//		ind[i + 2] = counter - 2;

//		ind[i + 3] = 0;
//		ind[i + 4] = 1;
//		ind[i + 5] = counter - 1;

//		ind[i + 6] = counter - 1;
//		ind[i + 7] = 1;
//		ind[i + 8] = 2;

//		ind[i + 9] = counter - 1;
//		ind[i + 10] = 2;
//		ind[i + 11] = counter;

//	}
//	else {
//		ind[i] = counter - 5;
//		ind[i + 1] = counter - 1;
//		ind[i + 2] = counter - 2;

//		ind[i + 3] = counter - 5;
//		ind[i + 4] = counter - 4;
//		ind[i + 5] = counter - 1;

//		ind[i + 6] = counter - 1;
//		ind[i + 7] = counter - 4;
//		ind[i + 8] = counter - 3;

//		ind[i + 9] = counter - 1;
//		ind[i + 10] = counter - 3;
//		ind[i + 11] = counter;
//		
//	}
//	counter = counter + 3;
//}
