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

#include "Observer.h"

class AssimpLoaderScene : public Scene
{
protected:
	void createShaders();
	void createModels();
public:
	AssimpLoaderScene(GLFWwindow* window);
	void applyLoadedModelSettings(GameObject* go, std::map<std::string, ShaderProgram*> shaderPrograms);
	using Scene::tick;
	void tick(float deltaTime);
	using Scene::draw;
	void draw();
};

