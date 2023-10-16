#pragma once
#include "GlobalInclude.h"

#include "Transforms/TransformComp.h"
#include <string>

class GameObject
{
protected:
	glm::vec3* position = new glm::vec3(0, 0, 0);
	glm::vec3* rotation = new glm::vec3(0, 0, 0);
	glm::vec3* scale = new glm::vec3(1, 1, 1);
public:
	std::string name;

	std::vector<GameObject*> childs;
	void addChild(GameObject* child);

	TransformComp* tc = new TransformComp();

	void setPosition(glm::vec3* pos);
	glm::vec3* getPosition() { return position; };

	void setRotation(glm::vec3* rot);
	glm::vec3* getRotation() { return rotation; };

	void setScale(glm::vec3* scl);
	glm::vec3* getScale() { return scale; };

	virtual void tick(double deltaTime);
	virtual void draw();
};

