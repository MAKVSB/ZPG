#pragma once
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram() {
	shaderProgram = glCreateProgram();
}

ShaderProgram::~ShaderProgram()
{
	for (Shader* shader : shaders) {
		delete shader;
	}
	glDeleteProgram(shaderProgram);
}

ShaderProgram* ShaderProgram::setCamera(Camera* cmr)
{
	if (camera != nullptr) {
		camera->remove(this);
	}
	camera = cmr;
	camera->add(this);
	listen(MessageType::CameraChanged, nullptr);
	return this;
}

void ShaderProgram::addShader(GLenum shaderType, std::string shaderFile) {
	shaders.push_back(new Shader(shaderType, shaderFile.c_str()));
}

void ShaderProgram::compile() {
	for (Shader* shader : shaders) {
		shader->compile();
		glAttachShader(shaderProgram, shader->getShader());
	}
	glLinkProgram(shaderProgram);
}

void ShaderProgram::cleanup() {
	while (!shaders.empty()) {
		Shader* shader = shaders.front();
		shaders.pop_front();
		glDetachShader(shaderProgram, shader->getShader());
		delete shader;
	}
}

bool ShaderProgram::check(GLchar* &errorMessage) {
	GLint status;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		errorMessage = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(shaderProgram, infoLogLength, NULL, errorMessage);
		return false;
	}
	return true;
}

void ShaderProgram::use() {
	glUseProgram(shaderProgram);
}

void ShaderProgram::unuse()
{
	glUseProgram(0);
}

int ShaderProgram::getUniformLocation(std::string uniformName)
{
	GLint dataLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
	if (dataLocation == -1) {
		std::cout << "WARNING: shader parameter location \"" << uniformName << "\" not found in shader " << shaderProgram << std::endl;
	}
	return dataLocation;
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, glm::mat4 M) {
	GLint dataLocation = getUniformLocation(uniformName);
	glProgramUniformMatrix4fv(shaderProgram, dataLocation, 1, GL_FALSE, &M[0][0]);
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, glm::vec3 V) {
	GLint dataLocation = getUniformLocation(uniformName);
	glProgramUniform3f(shaderProgram, dataLocation, V.x, V.y, V.z);
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, float f)
{
	GLint dataLocation = getUniformLocation(uniformName);
	glProgramUniform1f(shaderProgram, dataLocation, f);
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, int i)
{
	GLint dataLocation = getUniformLocation(uniformName);
	glProgramUniform1i(shaderProgram, dataLocation, i);
}

void ShaderProgram::listen(MessageType messageType, void* object)
{
	if (messageType == MessageType::CameraProjectionChange || messageType == MessageType::CameraChanged) {
		uploadUniformLocation("projectionMatrix", camera->getProjectionMartix());
	}
	if (messageType == MessageType::CameraViewChange || messageType == MessageType::CameraChanged) {
		uploadUniformLocation("viewMatrix", camera->getViewMatrix());
	}
}
