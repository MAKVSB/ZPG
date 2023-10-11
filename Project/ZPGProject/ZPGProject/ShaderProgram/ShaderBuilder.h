#pragma once
#include "GlobalInclude.h"

#include <string>
#include <filesystem>

#include "ShaderProgram/ShaderProgram.h"

class ShaderProgram;
class ShaderBuilder
{
	ShaderProgram* sp;

public:
	ShaderBuilder();
	ShaderBuilder* name(std::string name);
	ShaderBuilder* addShader(std::string shaderFolder);
	ShaderBuilder* addShader(const GLenum shaderType, const char* shaderFile);
	ShaderProgram* compileAndCheck();
};

