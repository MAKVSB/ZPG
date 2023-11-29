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
	auto cachedValue = uniformsLocationCache.find(uniformName);
	if (cachedValue == uniformsLocationCache.end()) {
		GLint dataLocation = glGetUniformLocation(shaderProgram, uniformName.c_str());
		if (dataLocation == -1) {
			std::cout << "WARNING: shader parameter location \"" << uniformName << "\" not found in shader " << shaderProgram << std::endl;
		}
		uniformsLocationCache[uniformName] = dataLocation;
	}
	return uniformsLocationCache[uniformName];
}

int ShaderProgram::getUniformBufferIndex(std::string uniformName) {
	auto cachedValue = uniformsLocationCache.find(uniformName);
	if (cachedValue == uniformsLocationCache.end()) {
		GLint dataLocation = glGetUniformBlockIndex(shaderProgram, uniformName.c_str());
		if (dataLocation == GL_INVALID_INDEX) {
			std::cout << "WARNING: shader parameter location \"" << uniformName << "\" not found in shader " << shaderProgram << std::endl;
			dataLocation = -1;
		}
		uniformsLocationCache[uniformName] = dataLocation;
	}
	return uniformsLocationCache[uniformName];
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, glm::mat4 M) {
	GLint dataLocation = getUniformLocation(uniformName);
	if (dataLocation != -1)
		glProgramUniformMatrix4fv(shaderProgram, dataLocation, 1, GL_FALSE, &M[0][0]);
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, glm::vec3 V) {
	GLint dataLocation = getUniformLocation(uniformName);
	if (dataLocation != -1)
		glProgramUniform3f(shaderProgram, dataLocation, V.x, V.y, V.z);
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, glm::vec2 V) {
	GLint dataLocation = getUniformLocation(uniformName);
	if (dataLocation != -1)
		glProgramUniform2f(shaderProgram, dataLocation, V.x, V.y);
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, float f)
{
	GLint dataLocation = getUniformLocation(uniformName);
	if (dataLocation != -1)
		glProgramUniform1f(shaderProgram, dataLocation, f);
}

void ShaderProgram::uploadUniformLocation(std::string uniformName, int i)
{
	GLint dataLocation = getUniformLocation(uniformName);
	if (dataLocation != -1)
		glProgramUniform1i(shaderProgram, dataLocation, i);
}

void ShaderProgram::listen(MessageType messageType, void* object)
{
	uploadUniformLocation("cameraPosition", *camera->getPosition());
	if (messageType == MessageType::CameraProjectionChange || messageType == MessageType::CameraChanged) {
		uploadUniformLocation("projectionMatrix", camera->getProjectionMartix());
	}
	if (messageType == MessageType::CameraViewChange || messageType == MessageType::CameraChanged) {
		uploadUniformLocation("viewMatrix", camera->getViewMatrix());
	}
}

void ShaderProgram::bindUniformObject(std::string uniformName, int bufferId, int bufferSize)
{
	GLuint blockIndex = getUniformBufferIndex(uniformName);
	if (blockIndex != -1) {
		GLint binding;
		glGetActiveUniformBlockiv(shaderProgram, blockIndex, GL_UNIFORM_BLOCK_BINDING, &binding);

		glUniformBlockBinding(shaderProgram, blockIndex, binding);
		glBindBufferBase(GL_UNIFORM_BUFFER, blockIndex, bufferId);
	}
}

void ShaderProgram::uploadUniformObject(int bufferId, int bufferSize, void* bufferData, int startPos) {
	glBindBuffer(GL_UNIFORM_BUFFER, bufferId);
	glBufferSubData(GL_UNIFORM_BUFFER, startPos, bufferSize, bufferData);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}
