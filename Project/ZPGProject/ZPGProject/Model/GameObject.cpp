#include "GameObject.h"

void GameObject::setPosition(glm::vec3 pos)
{
	position->x = pos.x;
	position->y = pos.y;
	position->z = pos.z;
}


void GameObject::setRotation(glm::vec3 rot)
{
	rotation->x = rot.x;
	rotation->y = rot.y;
	rotation->z = rot.z;
}

void GameObject::setScale(glm::vec3 scl)
{
	scale->x = scl.x;
	scale->y = scl.y;
	scale->z = scl.z;
}

void GameObject::tick(double deltaTime)
{
	for (GameObject* child : childs) {
		child->tick(deltaTime);
	}
}

void GameObject::draw()
{
	for (GameObject* child : childs) {
		child->draw();
	}
}

GameObject::GameObject()
{
	position = new glm::vec3(0, 0, 0);
	rotation = new glm::vec3(0, 0, 0);
	scale = new glm::vec3(1, 1, 1);
}


GameObject::~GameObject()
{
	for (auto child : childs) {
		delete child;
	}
	delete tc;
	delete position;
	delete rotation;
	delete scale;
}

void GameObject::addChild(GameObject* child)
{
	childs.emplace_back(child);
	TransformComp* test = child->tc;
	child->tc = new TransformComp();
	child->tc->add(tc);
	child->tc->add(test);
}