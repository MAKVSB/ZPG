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

void Camera::invalidate()
{
	notify(MessageType::CameraChanged, this);
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
	setMouseFree(false);
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
		if (keypressMap == nullptr) {
			keypressMap = dataStruct->map;
		}
	}
	if (messageType == MessageType::KeyReleased) {
		CallbackManager::CBKeyData* dataStruct = static_cast<CallbackManager::CBKeyData*>(object);
		if (keypressMap == nullptr) {
			keypressMap = dataStruct->map;
		}
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

void Camera::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
	if (keypressMap != nullptr) {
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
}

void Camera::draw() {
	GameObject::draw();
}

void Camera::drawDebugElement()
{
	ImGui::Begin("Object Debugger");
	std::string objectName(name);
	objectName += "Camera (" + std::to_string((uintptr_t)this) + ")";
	if (ImGui::TreeNode(objectName.c_str())) {
		if (ImGui::DragFloat3("Position", glm::value_ptr(*position), 0.1f, -100.0f, 100.0f)) {
			notify(MessageType::CameraChanged, this);
		}
		if (ImGui::DragFloat3("Rotation", glm::value_ptr(*rotation), 0.1f, -100.0f, 100.0f)) {
			notify(MessageType::CameraChanged, this);
		}
		if (ImGui::DragFloat3("Scale", glm::value_ptr(*scale), 0.1f, -100.0f, 100.0f)) {
			notify(MessageType::CameraChanged, this);
		}
		if (ImGui::DragFloat("FOV", &fov, 1, 0, 360)) {
			notify(MessageType::CameraChanged, this);
		}
		if (ImGui::DragFloat("yaw", &yaw, 1, -180, 180)) {
			notify(MessageType::CameraChanged, this);
		}
		if (ImGui::DragFloat("pitch", &pitch, 1, -90, 90)) {
			notify(MessageType::CameraChanged, this);
		}
		if (ImGui::DragFloat("speed", &camSpeed, 0.2f, 0, 100)) {
			notify(MessageType::CameraChanged, this);
		}
		if (ImGui::DragFloat("sensitivity", &camSensitivity, 0.01f, 0, 100)) {
			notify(MessageType::CameraChanged, this);
		}
		GameObject::drawDebugElement();
		ImGui::TreePop();
	}

	// End the window
	ImGui::End();
}
