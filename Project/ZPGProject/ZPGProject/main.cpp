﻿//Login MAK0065

#include "Application.h"

int main(void)
{
	Application* app = new Application();
	app->initialization(); //OpenGL inicialization
	
	//Loading scene
	app->createShaders();
	app->createModels();
	app->run();
}