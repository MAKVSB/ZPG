#pragma once
#include "../GlobalInclude.h"

#include <iostream>
#include <list>

#include "shader.h"
#include "Camera.h"
#include "Observer.h"
#include "ShaderBuilder.h"

class ShaderProgram : Observer
{
private:
	std::string name;
	std::list<Shader*> shaders;
	GLuint shaderProgram;
	Camera* camera = nullptr;

	void use();
	void unuse();

	void listen(MessageType messageType, void* object);

protected:
	friend class ShaderBuilder;
	//methods reserved to Shaderbuilder
	ShaderProgram();
	void compile();
	bool check(GLchar* &errorMessage);
	void addShader(GLenum shaderType, std::string shaderFile);

public:
	ShaderProgram* setCamera(Camera* camera);

	template<typename Func, typename... Args>
	void useWrapper(Func func, Args... args) {
		use();
		func(args...);
		unuse();
	}

	void uploadUniformMatrix(std::string uniformName, glm::mat4 M);
};
