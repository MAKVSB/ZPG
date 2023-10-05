#pragma once
#include "GlobalInclude.h"

#include <iostream>
#include <vector>

#include "ShaderProgram.h"
#include "TransformComp.h"

enum VertexDataFormat {
	POS_COLOR, // 0
};

class Model
{
private:
	GLuint VBO;
	VertexDataFormat dataFormat;
	int vertexLength;

public:
	Model(std::vector<float> vd, VertexDataFormat df = POS_COLOR);
	GLuint VAO;
	GLuint renderType = GL_TRIANGLES;
	ShaderProgram* shader;
	TransformComp* tc = new TransformComp();

	std::vector<float> vertexData;

	//translate local coords to global coords
	glm::vec3* position = new glm::vec3(0, 0, 0);
	glm::vec3* rotation = new glm::vec3(0, 0, 0);
	glm::vec3* scale = new glm::vec3(1);

	GLuint getVertexCount();
	void addTransforms();
	void draw();
};