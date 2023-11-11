#pragma once
#include "GlobalInclude.h"
#include <map>
#include "ShaderProgram/ShaderProgram.h"
#include "ShaderProgram/ShaderBuilder.h"
#include "Model/Model/Model.h"
#include "Model/Model/ModelLoader.h"
#include "Model/GameObject/GameObject.h"
#include "Camera.h"
#include "Light/Light.h"
#include "Light/LightManager.h"
#include "Model/Mesh/MeshManager.h"
#include "CallbackManager.h"
#include "Observer.h"
#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/GameObject/GameObjectBuilder.h"
#include "Light/Light.h"

class Scene
{
protected:
	GLFWwindow* window;
	Camera* camera;
	LightManager lightManager;
	MeshManager meshManager;
	std::unordered_map<std::string, Material> materialManager;

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

	virtual void tick(float deltaTime) {
		for (GameObject* element : models) {
			element->tick(deltaTime);
		}
	};

	virtual void draw() {
		for (GameObject* element : models) {
			element->draw();
		}
	}

	virtual void drawDebugElement() {
		for (GameObject* element : models) {
			element->drawDebugElement();
		}
	}
};
