#include "Camera.h"

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(position, position + rotation, up);
}

glm::mat4 Camera::getProjectionMartix() {
	if (activeProjection == Perspective) {
		return glm::perspective(fov, screenSize.x / screenSize.y, 0.1f, 100.0f);
	}
	else if (activeProjection == Orthogonal) {
		return glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, 0.0f, 100.0f);
	}
	else {
		return glm::mat4(1);
	}
}

Camera::Camera(GLFWwindow* wndw)
{
	window = wndw;
	CallbackManager::getInstance()->add(this);
	int width, height;
	glfwGetWindowSize(wndw, &width, &height);
	setScreenSize(width, height);
	glfwSetCursorPos(window, screenCenter.x, screenCenter.y);
}

void Camera::setScreenSize(float x, float y, bool notify)
{
	screenSize.x = x;
	screenSize.y = y;
	screenCenter.x = x / 2;
	screenCenter.y = y / 2;
	this->notify(MessageType::CameraProjectionChange, nullptr);
}

void Camera::listen(MessageType messageType, void* object)
{
	if (messageType == MessageType::WindowResize) {
		CallbackManager::CBResizeData* data = static_cast<CallbackManager::CBResizeData*>(object);
		setScreenSize(data->width, data->height);
		this->notify(MessageType::CameraProjectionChange, nullptr);
	}
	if (messageType == MessageType::KeyPressed) {
		CallbackManager::CBKeyData* dataStruct = static_cast<CallbackManager::CBKeyData*>(object);
		keypressMap[dataStruct->key] = dataStruct->mods + 1;

		if (dataStruct->key == GLFW_KEY_P) {
			switch (activeProjection)
			{
			case Perspective:
				activeProjection = Orthogonal;
				break;
			case Orthogonal:
				activeProjection = None;
				break;
			case None:
				activeProjection = Perspective;
				break;
			default:
				break;
			}
			this->notify(MessageType::CameraProjectionChange, nullptr);
		}
	}
	if (messageType == MessageType::KeyReleased) {
		CallbackManager::CBKeyData* dataStruct = static_cast<CallbackManager::CBKeyData*>(object);
		keypressMap[dataStruct->key] = 0;
	}
	if (messageType == MessageType::MouseMove) {
		CallbackManager::CBCursorData* dataStruct = static_cast<CallbackManager::CBCursorData*>(object);
		glfwSetCursorPos(window, screenCenter.x, screenCenter.y);

		yaw += (dataStruct->x - screenCenter.x) * camSensitivity;
		pitch += (screenCenter.y - dataStruct->y) * camSensitivity;
		//clamp values to prevent lock
		pitch = std::max(-89.9, std::min(pitch, 89.9));

		glm::vec3 dir;
		dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
		dir.y = sin(glm::radians(pitch));
		dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
		rotation = glm::normalize(dir);
		this->notify(MessageType::CameraViewChange, nullptr);
	}
}

void Camera::tick(double deltaTime)
{
	bool changed = false;
	float realSpeed = camSpeed * (float)deltaTime;

	if (keypressMap[GLFW_KEY_W] > 0) {
		position += realSpeed * rotation;
		changed = true;
	}
	if (keypressMap[GLFW_KEY_S] > 0) {
		position -= realSpeed * rotation;
		changed = true;
	}
	if (keypressMap[GLFW_KEY_SPACE] > 0) {
		position += realSpeed * up;
		changed = true;
	}
	if (keypressMap[GLFW_KEY_LEFT_CONTROL] > 0) {
		position -= realSpeed * up;
		changed = true;
	}
	if (keypressMap[GLFW_KEY_D] > 0 || keypressMap[GLFW_KEY_A] > 0) {
		glm::vec3 cameraRight = glm::normalize(glm::cross(rotation, up));
		if (keypressMap[GLFW_KEY_D] > 0) {
			position += realSpeed * cameraRight;
		}
		if (keypressMap[GLFW_KEY_A] > 0) {
			position -= realSpeed * cameraRight;
		}
		changed = true;
	}
	if (changed) this->notify(MessageType::CameraViewChange, nullptr);
}
