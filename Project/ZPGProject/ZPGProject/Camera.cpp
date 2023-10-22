#include "Camera.h"

glm::mat4 Camera::getViewMatrix() {
	return glm::lookAt(*position, *position + *rotation, up);
}

glm::mat4 Camera::getProjectionMartix() {
	if (activeProjection == Perspective) {
		return glm::perspective(fov, (float)screenSize.x / (float)screenSize.y, 0.1f, 100.0f);
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

	setPosition(glm::vec3(0, 0, 2));
	setRotation(glm::vec3(0, 0, -1));
	setMouseFree(true);
}

Camera::~Camera() {
	CallbackManager::getInstance()->remove(this);
}

void Camera::setScreenSize(int x, int y, bool notify)
{
	screenSize.x = x;
	screenSize.y = y;
	screenCenter.x = x / 2;
	screenCenter.y = y / 2;
	if (notify) this->notify(MessageType::CameraProjectionChange, nullptr);
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
		keypressMap = dataStruct->map;
	}
	if (messageType == MessageType::KeyReleased) {
		CallbackManager::CBKeyData* dataStruct = static_cast<CallbackManager::CBKeyData*>(object);
		keypressMap = dataStruct->map;
	}
	if (messageType == MessageType::MouseMove) {
		CallbackManager::CBCursorData* dataStruct = static_cast<CallbackManager::CBCursorData*>(object);

		if (!mouseFree) {
			glfwSetCursorPos(window, screenCenter.x, screenCenter.y);

			yaw += ((float)dataStruct->x - screenCenter.x) * camSensitivity;
			pitch += (screenCenter.y - (float)dataStruct->y) * camSensitivity;
			//clamp values to prevent lock
			pitch = std::max(-89.9f, std::min(pitch, 89.9f));

			glm::vec3 dir;
			dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			dir.y = sin(glm::radians(pitch));
			dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
			glm::vec3 normalizedDir = glm::normalize(dir);
			setRotation(normalizedDir);
			this->notify(MessageType::CameraViewChange, nullptr);
		}
	}
}

void Camera::setMouseFree(bool free) {
	mouseFree = free;
	glfwSetCursorPos(window, screenCenter.x, screenCenter.y);
	glfwSetInputMode(window, GLFW_CURSOR, free ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Camera::tick(double deltaTime)
{
	GameObject::tick(deltaTime);
	bool changed = false;
	float realSpeed = camSpeed * (float)deltaTime;

	if ((*keypressMap)[GLFW_KEY_W] > 0) {
		*position += realSpeed * *rotation;
		changed = true;
	}
	if ((*keypressMap)[GLFW_KEY_S] > 0) {
		*position -= realSpeed * *rotation;
		changed = true;
	}
	if ((*keypressMap)[GLFW_KEY_SPACE] > 0) {
		*position += realSpeed * glm::normalize(glm::cross(glm::cross(*rotation, up), *rotation));
		changed = true;
	}
	if ((*keypressMap)[GLFW_KEY_LEFT_CONTROL] > 0) {
		*position -= realSpeed * glm::normalize(glm::cross(glm::cross(*rotation, up), *rotation));
		changed = true;
	}
	if ((*keypressMap)[GLFW_KEY_D] > 0 || (*keypressMap)[GLFW_KEY_A] > 0) {
		glm::vec3 cameraRight = glm::normalize(glm::cross(*rotation, up));
		if ((*keypressMap)[GLFW_KEY_D] > 0) {
			*position += realSpeed * cameraRight;
		}
		if ((*keypressMap)[GLFW_KEY_A] > 0) {
			*position -= realSpeed * cameraRight;
		}
		changed = true;
	}
	if ((*keypressMap)[GLFW_KEY_LEFT_ALT] > 0 && !mouseFree) {
		setMouseFree(true);
	}
	if ((*keypressMap)[GLFW_KEY_LEFT_ALT] == 0 && mouseFree) {
		setMouseFree(false);
	}
	if (changed) this->notify(MessageType::CameraViewChange, nullptr);
}

void Camera::draw() {
	GameObject::draw();
}