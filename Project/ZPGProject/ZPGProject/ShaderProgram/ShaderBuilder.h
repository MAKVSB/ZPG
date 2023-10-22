/**
 * @file shaderBuilder.h
 *
 * @brief Builder for shader class. Allows safe loading of shaders.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "GlobalInclude.h"

#include <string>
#include <filesystem>

#include "ShaderProgram/ShaderProgram.h"

class ShaderProgram;
class ShaderBuilder
{
private:
	ShaderProgram* sp = new ShaderProgram();

public:
	ShaderBuilder& name(std::string name);
	ShaderBuilder& addShader(std::string shaderFolder);
	ShaderBuilder& addShader(const GLenum shaderType, const char* shaderFile);
	ShaderProgram* compileAndCheck();
};

