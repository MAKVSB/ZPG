#pragma once
#include "Shader.h"


std::string Shader::ReadShaderFile(const char* filePath)
{
    std::ifstream sourceFile(filePath, std::fstream::in);
    std::string sourceCode;
    if (sourceFile.is_open())
        sourceCode = std::string(std::istreambuf_iterator<char>(sourceFile),
            std::istreambuf_iterator<char>());
    return sourceCode;
}

Shader::Shader(GLenum shaderType, const char* shaderFile) {
	type = shaderType;
    code = ReadShaderFile(shaderFile);

    const char* fragmentShaderCodeCStr = code.c_str();
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &fragmentShaderCodeCStr, NULL);
}

void Shader::compile() {
	glCompileShader(shader);
}