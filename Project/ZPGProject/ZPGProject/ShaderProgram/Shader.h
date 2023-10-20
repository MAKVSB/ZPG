/**
 * @file Shader.h
 *
 * @brief Shader creation and compilation.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "../GlobalInclude.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include <string.h>

class Shader
{
private:
	static std::string ReadShaderFile(const char* filePath);

	GLenum type;
	std::string code;
	GLuint shader;
public:
	Shader(GLenum shaderType, const char* shaderCode);
	void compile();
	GLuint getShader() { return shader; };
};
