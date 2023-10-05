#pragma once
#include "Scene.h"

#include "Cube.h"
#include "Triangle.h"

class DefaultScene : public Scene
{
protected:
	void createShaders();
	void createModels();
public:
	DefaultScene(GLFWwindow* window);
	
	void tick(double deltaTime);
};

