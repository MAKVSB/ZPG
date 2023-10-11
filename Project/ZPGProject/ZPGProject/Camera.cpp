#include "Camera.h"

glm::mat4 Camera::getCameraMatrix() {
	return glm::lookAt(*position, *position + *targetPosition, *up);
}

glm::mat4 Camera::getProjectionMartix() {
	if (activeProjection == Perspective) {
		return glm::perspective(60.0f, screenSize.x / screenSize.y, 0.1f, 100.0f);
	}
	else if (activeProjection == Ortho) {
		return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	}
	else {
		return glm::mat4(1);
	}
}

Camera::Camera(GLFWwindow* window)
{
	CallbackManager::getInstance()->add(this);
	int width, height;
	glfwGetWindowSize(window, &width, &height);
	screenSize.x = (float)width;
	screenSize.y = (float)height;
}

void Camera::setScreenSize(float x, float y, bool notify)
{
	screenSize.x = x;
	screenSize.y = y;
	this->notify(MessageType::CameraStateChange, nullptr);
}

void Camera::listen(MessageType messageType, void* object)
{
	switch (messageType)
	{
	case MessageType::WindowResize:
		CallbackManager::CBResizeData* data = static_cast<CallbackManager::CBResizeData*>(object);
		setScreenSize(data->width, data->height);
		break;
	}
}
