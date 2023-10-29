#pragma once
#include "Model.h"

void Model::setVertexData(std::vector<float>* vd, VertexDataFormat df)
{
	vertexData = vd;
	dataFormat = df;

	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), vertexData->data(), GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	// Create a uniform buffer object
	materialUBO = 0;
	glGenBuffers(1, &materialUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, materialUBO);
	glBufferData(GL_UNIFORM_BUFFER, sizeof(Material), NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

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

void Model::setMaterial(Material m)
{
	this->material = m;
}

void Model::setShader(ShaderProgram* sp) {
	shader = sp;
}

Model::~Model()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &materialUBO);
}

GLuint Model::getVertexCount()
{
	return (int)vertexData->size() / vertexLength;
}

void Model::draw() {
	shader->uploadUniformLocation("modelMatrix", tc->transform());

	shader->bindUniformObject("Material", materialUBO, sizeof(Material));
	shader->uploadUniformObject(materialUBO, sizeof(Material), &material);

	shader->useWrapper([&]() {
		glBindVertexArray(VAO);
		// draw triangles
		glDrawArrays(renderType, 0, getVertexCount()); //mode,first,count
	});
	GameObject::draw();
}

void Model::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
}
