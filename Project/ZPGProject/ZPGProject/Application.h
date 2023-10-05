#pragma once
#include "GlobalInclude.h"

#include <iostream>

//Include the standard C++ headers  
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include <list>

#include "ShaderProgram.h"
#include "Model.h"

#include "Scene.h"
#include "DefaultScene.h"

class Application
{
private:
	GLFWwindow* window;

public:
	void initialization();
	void run();
};