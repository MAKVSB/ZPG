#pragma once
#include "GlobalInclude.h"
#include <map>
#include <list>
#include "ShaderProgram.h"
#include "Model.h"


class Scene
{
protected:
	GLFWwindow* window;

	std::map<std::string, ShaderProgram*> shaderPrograms;
	std::list<Model*> models;
public:
	Scene(GLFWwindow* window) {
		this->window = window;
		createShaders();
		createModels();
	};

	~Scene() {};

	void createShaders() {};
	void createModels() {};

	virtual void tick(double deltaTime) = 0;
};