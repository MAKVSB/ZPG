#pragma once
#include "GlobalInclude.h"

#include <iostream>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>
#include <thread>

#include "ShaderProgram/ShaderProgram.h"
#include "Model/Model.h"

#include "Scene/Scene.h"
//#include "Scene/DefaultScene/DefaultScene.h"
#include "Scene/SceneC5/SceneC5.h"

#include "CallbackManager.h"

class Application
{
private:
	GLFWwindow* window;

public:
	void initialization();
	void run();
};