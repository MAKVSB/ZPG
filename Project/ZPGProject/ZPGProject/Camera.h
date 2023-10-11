#pragma once
#include "GlobalInclude.h"

#include <algorithm>

#include "Observer.h"
#include "CallbackManager.h"

enum ProjectionEnum {
	Ortho,
	Perspective,
	None
};
class Camera : public Observable, public Observer
{
public:
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMartix();
private:

	//mouse controls
	double yaw = -90;
	double pitch = 0;
	float camSensitivity = 0.1f;

	//key controls
	std::map<int, int> keypressMap = std::map<int, int>();
	float camSpeed = 1.5f;

	GLFWwindow* window;

	glm::vec2 screenSize;
	glm::vec2 screenCenter;
	glm::vec3 position = glm::vec3(0, 0, 2);
	glm::vec3 direction = glm::vec3(0, 0, -1);
	glm::vec3 up = glm::vec3(0, 1, 0);
	float fov = 45;

	ProjectionEnum activeProjection = Perspective;

public:
	Camera(GLFWwindow* window);
	void setScreenSize(float x, float y, bool notify = true);
	void listen(MessageType messageType, void* object);
	void tick(double deltaTime);
};