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
#include "Model.h"

#include "Scene/Scene.h"
#include "Scene/DefaultScene.h"

#include "CallbackManager.h"

class Application
{
private:
	GLFWwindow* window;

public:
	void initialization();
	void run();
};