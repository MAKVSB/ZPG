#pragma once
#include "Scene.h"

#include "Models/Cube.h"
#include "Models/Triangle.h"
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Observer.h"

class DefaultScene : public Scene, public Observer
{
protected:
	void createShaders();
	void createModels();
public:
	DefaultScene(GLFWwindow* window);
	
	void tick(double deltaTime);

	void listen(MessageType messageType, void* object);
};

