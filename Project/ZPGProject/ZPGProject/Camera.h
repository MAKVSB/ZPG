#pragma once
#include "GlobalInclude.h"

#include "Observer.h"
#include "CallbackManager.h"

enum ProjectionEnum {
	Ortho,
	Perspective,
	None
};
class Camera : public Observable, public Observer
{
	glm::vec2 screenSize;
	glm::vec3* position = new glm::vec3(10, 10, 10);
	glm::vec3* targetPosition = new glm::vec3(0, 0, 0);
	glm::vec3* up = new glm::vec3(0, 1, 0);
	ProjectionEnum activeProjection = Perspective;


	glm::mat4 getCameraMatrix();
	glm::mat4 getProjectionMartix();
	
public:
	Camera(GLFWwindow* window);
	void setScreenSize(float x, float y, bool notify = true);

	void listen(MessageType messageType, void* object);
};