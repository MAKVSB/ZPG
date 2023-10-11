#include "ShaderBuilder.h"

#include <filesystem>

ShaderBuilder::ShaderBuilder()
{
	sp = new ShaderProgram();
}

ShaderBuilder* ShaderBuilder::name(std::string name)
{
	sp->name = name;
	return this;
}

ShaderBuilder* ShaderBuilder::addShader(std::string shaderFolder)
{
	if (std::filesystem::exists("./" + shaderFolder + "/vector.glsl")) {
		sp->addShader(GL_VERTEX_SHADER, ("./" + shaderFolder + "/vector.glsl").c_str());
	}
	if (std::filesystem::exists("./" + shaderFolder + "/fragment.glsl")) {
		sp->addShader(GL_FRAGMENT_SHADER, ("./" + shaderFolder + "/fragment.glsl").c_str());
	}
	return this;
}

ShaderBuilder* ShaderBuilder::addShader(const GLenum shaderType, const char* shaderFile)
{
	sp->addShader(shaderType, shaderFile);
	return this;
}

ShaderProgram* ShaderBuilder::compileAndCheck()
{
	sp->compile();
	GLchar* strInfoLog;
	if (!sp->check(strInfoLog)) {
		throw std::runtime_error("Linker failure: " + sp->name + "  -> " + strInfoLog);
		delete[] strInfoLog;
	}
	return sp;
}
