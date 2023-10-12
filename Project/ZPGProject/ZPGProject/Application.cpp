#pragma once
#include "Application.h"

void Application::initialization() {
	//void error_callback(int error, const char* description) { fputs(description, stderr); }
	//glfwSetErrorCallback(error_callback);

	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		exit(EXIT_FAILURE);
	}

	////inicializace konkretni verze
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	//glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	window = glfwCreateWindow(640, 480, "ZPG", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();

	// get version info
	printf("OpenGL Version: %s\n", glGetString(GL_VERSION));
	printf("Using GLEW %s\n", glewGetString(GLEW_VERSION));
	printf("Vendor %s\n", glGetString(GL_VENDOR));
	printf("Renderer %s\n", glGetString(GL_RENDERER));
	printf("GLSL %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	int major, minor, revision;
	glfwGetVersion(&major, &minor, &revision);
	printf("Using GLFW %i.%i.%i\n", major, minor, revision);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	float ratio = width / (float)height;
	glViewport(0, 0, width, height);

	//custom
	glEnable(GL_DEPTH_TEST);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	//init required singletons
	CallbackManager::init(window);
	
}

void Application::run() {
	double lastTickStartTime = glfwGetTime();
	Scene* defaultScene = new DefaultScene(window);
	//main vykreslovací while
	while (!glfwWindowShouldClose(window)) {
		double deltaTime = glfwGetTime() - lastTickStartTime;
		lastTickStartTime = glfwGetTime();

		defaultScene->tick(deltaTime);
		defaultScene->draw();
		//double drawingTime = glfwGetTime() - lastTickStartTime;
		//int fpsLimitSleepTime = (int)((1000 / 60 - drawingTime)*1000);
		//printf("fpslimiter %d\n", fpsLimitSleepTime);
		std::this_thread::sleep_for(std::chrono::milliseconds(5));
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
