/**
 * @file ShaderProgram.h
 *
 * @brief Full encapsulation of OpenGL Shaderprogram. Allows safe campilations, matrix uploads and other uses.
 *
 * @details  Safety of use() and unuse() commands
 *           use useWrapper() preferably with lambda functions.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "../GlobalInclude.h"

#include <iostream>
#include <list>

#include "shader.h"
#include "Camera.h"
#include "Observer.h"
#include "map"

class ShaderBuilder;
class ShaderProgram : Observer
{
private:
	std::string name;
	std::list<Shader*> shaders;
	GLuint shaderProgram;
	Camera* camera = nullptr;
	std::unordered_map<std::string, int> uniformsLocationCache;

	void use();
	void unuse();

	void listen(MessageType messageType, void* object);

	int getUniformLocation(std::string uniformName);
	int getUniformBufferIndex(std::string uniformName);
protected:
	friend class ShaderBuilder;
	//methods reserved to Shaderbuilder
	ShaderProgram();
	void compile();
	void cleanup();
	bool check(GLchar* &errorMessage);
	void addShader(GLenum shaderType, std::string shaderFile);
public:
	~ShaderProgram();
	ShaderProgram* setCamera(Camera* camera);


	template<typename Func, typename... Args>
	void useWrapper(Func func, Args... args) {
		use();
		func(args...);
		unuse();
	}

	void uploadUniformLocation(std::string uniformName, glm::mat4 M);
	void uploadUniformLocation(std::string uniformName, glm::vec3 V);
	void uploadUniformLocation(std::string uniformName, glm::vec2 V);
	void uploadUniformLocation(std::string uniformName, float f);
	void uploadUniformLocation(std::string uniformName, int i);
	void bindUniformObject(std::string uniformName, int bufferId, int bufferSize);
	static void uploadUniformObject(int bufferId, int bufferSize, void* bufferData, int startPos = 0);
};
