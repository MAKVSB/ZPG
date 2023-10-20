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

#include "Models/Cube.h"
#include "Models/Triangle.h"
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Observer.h"

class DefaultScene : public Scene
{
protected:
	void createShaders();
	void createModels();
public:
	DefaultScene(GLFWwindow* window);
	using Scene::tick;
	void tick(double deltaTime);
	using Scene::draw;
	void draw();
};

