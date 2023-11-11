/**
 * @file GameObject.h
 *
 * @brief Application object. Defines basic properties and methods which all properties in scene must have.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "GlobalInclude.h"

#include "Transforms/TransformComp.h"
#include "Observer.h"
#include <string>

class GameObject
{
protected:
	glm::vec3* position;
	glm::vec3* rotation;
	glm::vec3* scale;
public:
	GameObject();
	virtual ~GameObject();

	std::string name;

	std::vector<GameObject*> childs;
	void addChild(GameObject* child);

	TransformComp* tc = new TransformComp();

	void setPosition(glm::vec3 pos);
	void updatePosition(glm::vec3 pos);
	glm::vec3* getPosition() { return position; };

	void setRotation(glm::vec3 rot);
	void updateRotation(glm::vec3 pos);
	glm::vec3* getRotation() { return rotation; };

	void setScale(glm::vec3 scl);
	void updateScale(glm::vec3 pos);
	glm::vec3* getScale() { return scale; };

	virtual bool isCamera() { return false; };
	virtual bool isModel() { return false; };
	virtual bool isLight() { return false; };
	virtual bool isGroup() { return !(isCamera() || isModel() || isLight()); };

	virtual void tick(float deltaTime);
	virtual void draw();
	virtual void drawDebugElement();

	virtual void invalidate();
};

