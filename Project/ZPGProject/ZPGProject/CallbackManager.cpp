#pragma once
#include "GlobalInclude.h"

#include "CallbackManager.h"

void CallbackManager::cbError(int error, const char* description) {
	fputs(description, stderr);
}

void CallbackManager::cbKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
		printf("key_callback [%d,%d,%d,%d] \n", key, scancode, action, mods);
}

void CallbackManager::cbCursor(GLFWwindow* window, double x, double y) {
	printf("cursor_callback \n");
}

void CallbackManager::cbButton(GLFWwindow* window, int button, int action, int mode) {
	if (action == GLFW_PRESS) printf("button_callback [%d,%d,%d]\n", button, action, mode);
}

void CallbackManager::cbWindowFocus(GLFWwindow* window, int focused) { printf("window_focus_callback \n"); }

void CallbackManager::cbIconify(GLFWwindow* window, int iconified) { printf("window_iconify_callback \n"); }

void CallbackManager::cbResize(GLFWwindow* window, int width, int height) {
	printf("resize %d, %d \n", width, height);
	glViewport(0, 0, width, height);
}

void CallbackManager::registerCallbacks(GLFWwindow* window) {
	glfwSetErrorCallback(CallbackManager::cbError);
	glfwSetKeyCallback(window, CallbackManager::cbKey);
	glfwSetCursorPosCallback(window, CallbackManager::cbCursor);
	glfwSetMouseButtonCallback(window, CallbackManager::cbButton);
	glfwSetWindowFocusCallback(window, CallbackManager::cbWindowFocus);
	glfwSetWindowIconifyCallback(window, CallbackManager::cbIconify);
	glfwSetWindowSizeCallback(window, CallbackManager::cbResize);
}

CallbackManager::CallbackManager(GLFWwindow* window) {
	registerCallbacks(window);
}