#pragma once
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram() {
	shaderProgram = glCreateProgram();
}

void ShaderProgram::addShader(GLenum shaderType, const char* shaderFile) {
	shaders.push_back(new Shader(shaderType, shaderFile));
}

void ShaderProgram::compile() {
	for (Shader* shader : shaders) {
		shader->compile();
		glAttachShader(shaderProgram, shader->getShader());
	}
	glLinkProgram(shaderProgram);
}

bool ShaderProgram::check() {
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
		return false;
	}
	return true;
}

void ShaderProgram::use() {
	glUseProgram(shaderProgram);
}