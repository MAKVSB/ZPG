#pragma once
#include "GlobalInclude.h"

#include <algorithm>

#include "Observer.h"
#include "CallbackManager.h"
#include "Model/GameObject.h"

enum ProjectionEnum {
	Orthogonal,
	Perspective,
	None
};
class Camera : public Observable, public Observer, public GameObject
{
private:
	//key controls
	std::map<int, int>* keypressMap = new std::map<int, int>();

	GLFWwindow* window;

	glm::ivec2 screenSize;
	glm::ivec2 screenCenter;
	glm::vec3 up = glm::vec3(0, 1, 0);

	ProjectionEnum activeProjection = Perspective;

public:
	float fov = 45;
	float yaw = -90;
	float pitch = 0;
	float camSensitivity = 0.1f;
	float camSpeed = 1.5f;


	Camera(GLFWwindow* window);
	void setScreenSize(int x, int y, bool notify = true);
	void listen(MessageType messageType, void* object);
	using GameObject::tick;
	void tick(double deltaTime);
	using GameObject::draw;
	void draw();

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMartix();

};