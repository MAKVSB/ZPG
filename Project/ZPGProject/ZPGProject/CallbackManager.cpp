#pragma once
#include "GlobalInclude.h"

#include "CallbackManager.h"
CallbackManager* CallbackManager::instance = nullptr;
GLFWwindow* CallbackManager::window = nullptr;

void CallbackManager::cbError(int error, const char* description) {
	fputs(description, stderr);
}

void CallbackManager::cbKey(GLFWwindow* window, int key, int scancode, int action, int mods) {
	CBKeyData cbData = CBKeyData{ key, mods };
	switch (action)
	{
	case GLFW_PRESS:
		if (key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GL_TRUE);
		instance->notify(MessageType::KeyPressed, &cbData);
		break;
	case GLFW_REPEAT:
		instance->notify(MessageType::KeyHeld, &cbData);
		break;
	case GLFW_RELEASE:
		instance->notify(MessageType::KeyReleased, &cbData);
		break;
	}
}

void CallbackManager::cbButton(GLFWwindow* window, int button, int action, int mods) {
	CBButtonData cbData = CBButtonData{ button, mods };
	switch (action)
	{
	case GLFW_PRESS:
		instance->notify(MessageType::MouseButtonPressed, &cbData);
		break;
	case GLFW_RELEASE:
		instance->notify(MessageType::MouseButtonReleased, &cbData);
		break;
	}
}

void CallbackManager::cbCursor(GLFWwindow* window, double x, double y) {
	CBCursorData cbData = CBCursorData{ x, y };
	instance->notify(MessageType::MouseMove, &cbData);
}

void CallbackManager::cbResize(GLFWwindow* window, int width, int height) {
	CBResizeData cbData = CBResizeData{ width, height };
	instance->notify(MessageType::WindowResize, &cbData);
	glViewport(0, 0, width, height);
}

void CallbackManager::cbScroll(GLFWwindow* window, double xoffset, double yoffset)
{
	CBScrollData cbData = CBScrollData{ xoffset, yoffset };
	instance->notify(MessageType::ScrollOffsetChange, &cbData);
}

void CallbackManager::cbWindowFocus(GLFWwindow* window, int focused) { 
	CBFocusData cbData = CBFocusData{ (bool)focused };
	instance->notify(MessageType::WindowFocusChange, &cbData);
}

void CallbackManager::cbIconify(GLFWwindow* window, int iconified) {
	CBIconifyData cbData = CBIconifyData{ (bool)iconified };
	instance->notify(MessageType::WindowVisibleChange, &cbData);
	printf("window_iconify_callback \n");
}


void CallbackManager::registerCallbacks(GLFWwindow* window) {
	glfwSetErrorCallback(cbError);
	glfwSetKeyCallback(window, cbKey);
	glfwSetCursorPosCallback(window, cbCursor);
	glfwSetMouseButtonCallback(window, cbButton);
	glfwSetWindowFocusCallback(window, cbWindowFocus);
	glfwSetWindowIconifyCallback(window, cbIconify);
	glfwSetWindowSizeCallback(window, cbResize);
	glfwSetScrollCallback(window, cbScroll);
}

void CallbackManager::unregisterCallbacks(GLFWwindow* window) {
	glfwSetErrorCallback(nullptr);
	glfwSetKeyCallback(window, nullptr);
	glfwSetCursorPosCallback(window, nullptr);
	glfwSetMouseButtonCallback(window, nullptr);
	glfwSetWindowFocusCallback(window, nullptr);
	glfwSetWindowIconifyCallback(window, nullptr);
	glfwSetWindowSizeCallback(window, nullptr);
	glfwSetScrollCallback(window, nullptr);
}

CallbackManager::~CallbackManager() {
	unregisterCallbacks(window);
	instance = nullptr;
	window = nullptr;
}

CallbackManager::CallbackManager(GLFWwindow* window) {
	CallbackManager::window = window;
	registerCallbacks(window);
}