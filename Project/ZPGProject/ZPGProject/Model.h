#pragma once
#include <iostream>
#include <vector>

#include <GL/glew.h>
#include "ShaderProgram.h"

enum VertexDataFormat {
	POS_COLOR, // 0
};

class Model
{
private:
	GLuint VBO;
	VertexDataFormat dataFormat;


public:
	Model(std::vector<float> vd, VertexDataFormat df = POS_COLOR);
	GLuint VAO;
	GLuint renderType = GL_TRIANGLES;
	GLuint getVertexCount();
	void draw();
	ShaderProgram* shader;

	std::vector<float> vertexData;
};