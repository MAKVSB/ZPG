#pragma once
#include "GlobalInclude.h"
#include <map>
#include <regex>
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

	bool indexUsageMap[255] = { 0 };
public:

	Scene(GLFWwindow* wndw);
	virtual ~Scene();

	void createShaders();
	void createModels();

	virtual void tick(float deltaTime);
	virtual void draw();
	virtual void drawDebugElement();

	bool matchWithWildcard(const std::string& pattern, const std::string& text);
	GameObject* getGameObjectByIndexRecursive(std::vector<GameObject*> mdls, int index, std::string nameFilterPattern);
	GameObject* getGameObjectByIndex(int index, std::string nameFilterPattern = "");
	int getUnusedIndex(int min = 1, int max = 254);
};
