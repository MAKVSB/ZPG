#pragma once
#include "Scene/Scene.h"

#include "Models/Cube.h"
#include "Models/Triangle.h"
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Observer.h"

class SceneC5 : public Scene
{
protected:
	void createShaders();
	void createModels();
public:
	SceneC5(GLFWwindow* window);
	using Scene::tick;
	void tick(double deltaTime);
	using Scene::draw;
	void draw();
};

