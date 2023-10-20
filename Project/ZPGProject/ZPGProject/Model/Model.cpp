#pragma once
#include "Model.h"

void Model::setVertexData(std::vector<float> vd, VertexDataFormat df)
{
	vertexData = vd;
	dataFormat = df;

	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	switch (dataFormat)
	{
	case POS4_COL4:
		vertexLength = 8;
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)(4 * sizeof(float)));
		break;
	case POS3_NOR3:
		vertexLength = 6;
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)0);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		break;
	}
}

GLuint Model::getVertexCount()
{
	return vertexData.size() / vertexLength;
}

void Model::draw() {
	shader->uploadUniformMatrix("modelMatrix", tc->transform());
	//shader->uploadUniformMatrix("normalMatrix", glm::mat3(tc->transform()));


	shader->useWrapper([&]() {
		glBindVertexArray(VAO);
		// draw triangles
		glDrawArrays(renderType, 0, getVertexCount()); //mode,first,count
	});
}

void Model::tick(double deltaTime)
{
	GameObject::tick(deltaTime);
}
