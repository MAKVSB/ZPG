#pragma once
#include "Application.h"

Application::~Application()
{
	delete sm;
	delete currentScene;
}

void Application::initialization() {
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

	//init required singletons
	CallbackManager::init(window);
	CallbackManager::getInstance()->add(this);
	sm = new SceneManager(window);
	sm->registerScenes();
}

void Application::run() {
	bool prefectTime = true;
	int targetFPS = 60;
	double targetFrameTime = (double)1000 / targetFPS - 2; // (-const) just to be slightly above set framerate

	double lastTickStartTime = glfwGetTime();
	double thisTickStartTime, deltaTime;

	currentScene = sm->sceneSelector();
	//main vykreslovací while
	while (!glfwWindowShouldClose(window)) {
		deltaTime = glfwGetTime() - lastTickStartTime;
		lastTickStartTime = glfwGetTime();
		thisTickStartTime = lastTickStartTime;

		if (currentScene) {
			currentScene->tick((float)deltaTime);
			currentScene->draw();
		}

		double thisTickElapsed = glfwGetTime() - thisTickStartTime;
		double sleepTime = targetFrameTime - thisTickElapsed * 1000;
		if (prefectTime) {
			while (1) {
				thisTickElapsed = glfwGetTime() - thisTickStartTime;
				if (targetFrameTime - thisTickElapsed * 1000 < 1) {
					break;
				}
			}
		}
		else {
			std::this_thread::sleep_for(std::chrono::milliseconds((int)(sleepTime/2)));
		}

		//printf("Current FPS: %d\n", (int)(1 / deltaTime));
		// update other events like input handling
		glfwPollEvents();
		// put the stuff we’ve been drawing onto the display
		glfwSwapBuffers(window);
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}

void Application::listen(MessageType messageType, void* object)
{
	if (MessageType::KeyPressed == messageType) {
		CallbackManager::CBKeyData* data = static_cast<CallbackManager::CBKeyData*>(object);
		if (data->key == GLFW_KEY_GRAVE_ACCENT) {
			delete currentScene;
			currentScene = sm->sceneSelector();
		}
	}
}
