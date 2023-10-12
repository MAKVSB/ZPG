#pragma once
#include "../GlobalInclude.h"
#include <map>
#include <list>
#include "ShaderProgram/ShaderProgram.h"
#include "ShaderProgram/ShaderBuilder.h"
#include "Model/Model.h"
#include "Model/ModelLoader.h"
#include "Model/GameObject.h"
#include "Camera.h"

class Scene
{
protected:
	GLFWwindow* window;
	Camera* camera;

	std::map<std::string, ShaderProgram*> shaderPrograms;
	std::list<GameObject*> models;
public:
	Scene(GLFWwindow* window) {
		this->window = window;
		createShaders();
		createModels();
		camera = new Camera(window);
		models.push_back(camera);
	};

	~Scene() {};

	void createShaders() {};
	void createModels() {};

	virtual void tick(double deltaTime) = 0;
	virtual void draw() = 0;
};