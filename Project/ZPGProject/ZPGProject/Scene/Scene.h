#pragma once
#include "../GlobalInclude.h"
#include <map>
#include <list>
#include "ShaderProgram/ShaderProgram.h"
#include "Model.h"
#include "Camera.h"

class Scene
{
protected:
	GLFWwindow* window;
	Camera* camera;

	std::map<std::string, ShaderProgram*> shaderPrograms;
	std::list<Model*> models;
public:
	Scene(GLFWwindow* window) {
		this->window = window;
		createShaders();
		createModels();
		camera = new Camera(window);
	};

	~Scene() {};

	void createShaders() {};
	void createModels() {};

	virtual void tick(double deltaTime) = 0;
};