#pragma once
#include "GlobalInclude.h"

#include <iostream>
#include <vector>

#include "ShaderProgram/ShaderProgram.h"
#include "Transforms/TransformComp.h"
#include "Model/GameObject.h"

enum VertexDataFormat {
	POS4_COL4,
	POS3_NOR3,
};

class Model : public GameObject
{
private:
	GLuint VBO;
	VertexDataFormat dataFormat;
	int vertexLength;

public:
	GLuint VAO;
	GLuint renderType = GL_TRIANGLES;
	ShaderProgram* shader;

	std::vector<float> vertexData;

	void setVertexData(std::vector<float> vd, VertexDataFormat df = POS4_COL4);

	GLuint getVertexCount();
	void addTransforms();
	using GameObject::draw;
	void draw() override;
	using GameObject::tick;
	void tick(double deltaTime);
};