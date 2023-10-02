#pragma once
#include <iostream>
#include <list>

#include <GL/glew.h>

#include "shader.h"

class ShaderProgram
{
private:
	std::list<Shader*> shaders;
	GLuint shaderProgram;

public:
	ShaderProgram();
	void compile();
	bool check();
	void use();
	void addShader(GLenum shaderType, const char* shaderFile);
};
