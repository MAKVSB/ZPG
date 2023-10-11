#pragma once
#include "GlobalInclude.h"

#include <iostream>
#include <vector>

#include "ShaderProgram/ShaderProgram.h"
#include "Transforms/TransformComp.h"

enum VertexDataFormat {
	POS4_COL4,
	POS3_NOR3,
};

class Model
{
private:
	GLuint VBO;
	VertexDataFormat dataFormat;
	int vertexLength;

public:
	Model(std::vector<float> vd, VertexDataFormat df = POS4_COL4);
	GLuint VAO;
	GLuint renderType = GL_TRIANGLES;
	ShaderProgram* shader;
	TransformComp* tc = new TransformComp();

	std::vector<float> vertexData;

	//translate local coords to global coords
	glm::vec3* positionRelToWorld = new glm::vec3(0, 0, 0);
	glm::vec3* positionRelToCenter = new glm::vec3(0, 0, 0);
	glm::vec3* rotationRelToCenter = new glm::vec3(0, 0, 0);
	glm::vec3* scale = new glm::vec3(1);

	GLuint getVertexCount();
	void addTransforms();
	void draw();
};