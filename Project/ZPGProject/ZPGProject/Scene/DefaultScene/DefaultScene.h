/**
 * @file DefaultScene.h
 *
 * @brief Application scene showcasing rowk made in first lessons.
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

class DefaultScene : public Scene
{
protected:
	void createShaders();
	void createModels();
public:
	DefaultScene(GLFWwindow* window);
	using Scene::tick;
	void tick(float deltaTime);
	using Scene::draw;
	void draw();
};
