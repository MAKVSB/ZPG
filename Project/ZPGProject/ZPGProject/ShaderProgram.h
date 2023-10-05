#pragma once
#include "GlobalInclude.h"

#include <iostream>
#include <list>

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
	void uploadUniformLocation(std::string uniformName, glm::mat4 M);

};
