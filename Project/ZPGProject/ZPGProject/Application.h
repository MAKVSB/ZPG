/**
 * @file Application.h
 *
 * @brief Application main point
 *
 * @author Daniel Makovsky (original author Maritn Nemec 2023)
 *
 * @year 2023
 **/
#define _CRTDBG_MAP_ALLOC

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
#include "Model/Model/Model.h"
#include "Observer.h"

#include "Scene/SceneManager.h"
#include "Scene/Scene.h"

#include "CallbackManager.h"

class Application : Observer
{
private:
	GLFWwindow* window;
	void inicializeOpenGL();
	void inicializeImgui();

	bool imguiEnabled = true;

public:
	Scene* currentScene;
	SceneManager* sm;

	~Application();

	void initialization();
	void run();

	// Dìdí se pøes Observer.
	void listen(MessageType messageType, void* object);
};