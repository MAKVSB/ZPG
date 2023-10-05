#pragma once
#include "Model.h"

Model::Model(std::vector<float> vd, VertexDataFormat df) {
	vertexData = vd;
	dataFormat = df;

	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size()*sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glEnableVertexAttribArray(0); //enable vertex attributes
	glEnableVertexAttribArray(1); 
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	switch (dataFormat)
	{
	case POS_COLOR:
		glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)0);
		glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(4 * sizeof(float)));
		vertexLength = 8;
		break;
	}
}

void Model::addTransforms() {
	//tc->resetTransformMatrix();
	//tc->addRotationTransform(rotation);
	//tc->addTranlateTransform(position);
	//tc->addScaleTransform(scale);
}

GLuint Model::getVertexCount()
{
	return vertexData.size() / vertexLength;
}

void Model::draw() {
	addTransforms();
	shader->use();
	shader->uploadUniformLocation("modelMatrix", tc->transform());

	glBindVertexArray(VAO);

	// draw triangles
	glDrawArrays(renderType, 0, getVertexCount()); //mode,first,count
}
