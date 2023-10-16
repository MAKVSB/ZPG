#pragma once
#include "ShaderProgram.h"


ShaderProgram::ShaderProgram() {
	shaderProgram = glCreateProgram();
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

void ShaderProgram::uploadUniformMatrix(std::string uniformName, glm::mat4 M) {
	use();
	GLint dataLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
	if (dataLocation == -1) {
		std::cout << "WARNING: shader parameter location \"" << uniformName << "\" not found in shader " << shaderProgram << std::endl;
	}
	glUniformMatrix4fv(dataLocation, 1, GL_FALSE, &M[0][0]);
	unuse();
}

void ShaderProgram::listen(MessageType messageType, void* object)
{
	if (messageType == MessageType::CameraProjectionChange || messageType == MessageType::CameraChanged) {
		uploadUniformMatrix("projectionMatrix", camera->getProjectionMartix());
	}
	if (messageType == MessageType::CameraViewChange || messageType == MessageType::CameraChanged) {
		uploadUniformMatrix("viewMatrix", camera->getViewMatrix());
	}
}
