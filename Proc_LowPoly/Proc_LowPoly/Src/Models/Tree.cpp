#include "Tree.h"



Tree::Tree(int _Edges, float _Thickness)
{
	Thickness = _Thickness;
	shader = new Shader("Shaders/Tree/TreeV.glsl", "Shaders/Tree/TreeF.glsl", "Shaders/Tree/TreeG.glsl");
	if (_Edges < 4)
	{
		Edges = 4;
	}
	else
	{
		Edges = _Edges;
	}
	L_System3D L("X", "FFF[+{&FFF0]FF[&\X]FFF0", "FF", 2, glm::vec3(0.0, 1.0, 0.0), 45, 1.0f);
	Structure = L.CreateSystem();
	vertices.resize((Structure.size()*2)*Edges);
	indices.resize((Structure.size()+10)*(Edges*2*3));
	CreateMesh(vertices, indices);

	for each (Segment3D seg in Structure)
	{
		if (seg.type == EndL)
		{
			ends.push_back(seg);
		}
	}

	sphere.createSphere(4, 4);
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


Tree::~Tree()
{
	delete shader;
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}

void Tree::Render(glm::mat4 projection, glm::mat4 view)
{
	//Start shader
	shader->use();

	//Send variables to shader
	shader->setMat4("projection", projection);
	shader->setMat4("view", view);
	glm::mat4 model = glm::translate(glm::vec3(0.0, 0.0, 0.0));
	shader->setMat4("model", model);
	shader->setFloat("Time", glfwGetTime());
	shader->setVec3("color", glm::vec3(0.6, 0.28, 0.08));
	shader->setBool("Stem", true);

	//Bind the VAO and draw the vertex
	glBindVertexArray(VAO);
	//glDrawArrays(GL_TRIANGLES, 0, 2*SIZE*SIZE);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

	
	for each (Segment3D pos in ends)
	{
		shader->setVec3("color", glm::vec3(0.0, 0.5, 0.0));
		model = glm::translate(pos.End)*glm::scale(glm::vec3(pos.width));
		shader->setMat4("model", model);

		shader->setBool("Stem", false);
		sphere.render();
	}

}

void Tree:: UpdateShader()
{
	glDeleteProgram(shader->ID);
	shader = new Shader("Shaders/Tree/TreeV.glsl", "Shaders/Tree/TreeF.glsl", "Shaders/Tree/TreeG.glsl");
}

void Tree::CreateMesh(std::vector<Vertex> &vert, std::vector<unsigned int> &ind)
{
	int counter = 0;
	float degree = 360.0 / Edges;
	for each (Segment3D seg in Structure)
	{
		Vertex temp;
		//Make a vertex displace in the perpendicular to the direction
		for (int i = 0; i < Edges; i++)
		{
			//Create an offset from origo on how much displacement that will be from the point.
			glm::vec3 t = glm::rotate(glm::mat4(1.0f), (float)(i*degree*D2R), glm::normalize(seg.Direction))*glm::vec4(seg.Orto,1.0)*seg.width;
			// Add the offset to the point
			glm::vec3 rot = seg.Start+t;
			temp = Vertex{ rot };
			vert[counter] = temp;
			counter++;
		}
		//If it is the last point on a branch
		if (seg.type == EndL || seg.type == BranchL)
		{
			for (int i = 0; i < Edges; i++)
			{
				glm::vec3 t = glm::rotate(glm::mat4(1.0f), (float)(i*degree*D2R), glm::normalize(seg.Direction))*glm::vec4(seg.Orto, 1.0)*seg.width;
				glm::vec3 rot = seg.End + t;
				temp = Vertex{ rot };
				vert[counter] = temp;
				counter++;
			}
		}
	}
	/*for each (Vertex var in vert)
	{
		std::cout << var.Position.x << "\t\t " << var.Position.y << "\t\t " << var.Position.z <<std::endl;
	}*/

	counter = 0;
	for each (Segment3D seg in Structure)
	{
		int SegmentLevel = counter * Edges * 6;
		//Loop over all the squares
		for (int i = 0; i < Edges; i++)
		{
			if (i == Edges - 1)
			{
				//Bind last vertexes againt the first
				ind[SegmentLevel + i * 6 + 0] = counter * Edges + i;
				ind[SegmentLevel + i * 6 + 1] = counter * Edges + 0;
				ind[SegmentLevel + i * 6 + 2] = counter * Edges + i + Edges;

				ind[SegmentLevel + i * 6 + 3] = counter * Edges + 0;
				ind[SegmentLevel + i * 6 + 4] = counter * Edges + Edges;
				ind[SegmentLevel + i * 6 + 5] = counter * Edges + i + Edges;
			}
			else {
				//Standard
				ind[SegmentLevel + i * 6 + 0] = counter * Edges + i;
				ind[SegmentLevel + i * 6 + 1] = counter * Edges + i + 1;
				ind[SegmentLevel + i * 6 + 2] = counter * Edges + i + Edges;

				ind[SegmentLevel + i * 6 + 3] = counter * Edges + i + 1;
				ind[SegmentLevel + i * 6 + 4] = counter * Edges + i + Edges + 1;
				ind[SegmentLevel + i * 6 + 5] = counter * Edges + i + Edges;
			}
		}
		//Increment counter depending on the type
		if (seg.type == EndL || seg.type == BranchL)
		{
			counter = counter + 2;
		}
		else {
			counter++;
		}
	}

}