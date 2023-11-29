/**
 * @file SceneC5.h
 *
 * @brief Scene for showcasing light shaders.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "Scene/Scene.h"

extern const float cubeVertexData[];
extern const float triangleVertexData[];
extern const float sphere[];
extern const float suziFlat[];
extern const float suziSmooth[];

class AssimpLoaderScene : public Scene, Observer
{
protected:
	void createShaders();
	void createModels();
	void applyLoadedModelSettings(GameObject* go);
public:

	struct FlickerLight {
		Light* light;
		float duration;
		float maxFrequency;
	};
	std::vector<FlickerLight> flickeringLights;
	std::vector<GameObject*> treeGrowQueue;
	std::vector<GameObject*> treeShrinkQueue;

	AssimpLoaderScene(GLFWwindow* window);
	~AssimpLoaderScene();
	using Scene::tick;
	void tick(float deltaTime);
	using Scene::draw;
	//void draw();
	using Scene::drawDebugElement;
	void drawDebugElement();

	void listen(MessageType messageType, void* object);
};

