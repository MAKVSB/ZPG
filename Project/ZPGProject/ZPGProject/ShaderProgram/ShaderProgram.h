#pragma once
#include "../GlobalInclude.h"

#include <iostream>
#include <list>

#include "shader.h"
#include "Camera.h"
#include "Observer.h"

class ShaderProgram : Observer
{
private:
	std::list<Shader*> shaders;
	GLuint shaderProgram;
	Camera* camera = nullptr;

public:
	ShaderProgram();
	void setCamera(Camera* camera);
	void compile();
	bool check();
	void use();
	void unuse();
	void addShader(GLenum shaderType, const char* shaderFile);
	void uploadUniformMatrix(std::string uniformName, glm::mat4 M);

	// Dìdí se pøes Observer.
	void listen(MessageType messageType, void* object);
};
