#pragma once
#include "GlobalInclude.h"
#include <map>
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
	std::vector<GameObject*> models;
public:

	Scene(GLFWwindow* wndw) {
		window = wndw;
		createShaders();
		createModels();
		camera = new Camera(window);
		models.push_back(camera);
	};

	~Scene() {
		for (auto sp : shaderPrograms) {
			delete sp.second;
		}
		for (auto model : models) {
			delete model;
		}
	};

	void createShaders() {};
	void createModels() {};

	virtual void tick(double deltaTime) {
		for (GameObject* element : models) {
			element->tick(deltaTime);
		}
	};

	virtual void draw() {
		for (GameObject* element : models) {
			element->draw();
		}
	}
};
