/**
 * @file Application.h
 *
 * @brief Application main point
 *
 * @author Daniel Makovsky (original author Maritn Nemec 2023)
 *
 * @year 2023
 **/

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