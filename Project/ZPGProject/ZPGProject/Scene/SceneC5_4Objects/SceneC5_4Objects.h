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

class SceneC5_4Objects : public Scene
{
protected:
	void createShaders();
	void createModels();
public:
	SceneC5_4Objects(GLFWwindow* window);
	using Scene::tick;
	void tick(float deltaTime);
	using Scene::draw;
	void draw();
};

