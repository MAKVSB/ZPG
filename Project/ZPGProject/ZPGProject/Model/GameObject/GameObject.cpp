#include "GameObject.h"

void GameObject::setPosition(glm::vec3 pos)
{
	position->x = pos.x;
	position->y = pos.y;
	position->z = pos.z;
	invalidate();
}

void GameObject::updatePosition(glm::vec3 pos)
{
	position->x += pos.x;
	position->y += pos.y;
	position->z += pos.z;
	invalidate();
}

void GameObject::setRotation(glm::vec3 rot)
{
	rotation->x = rot.x;
	rotation->y = rot.y;
	rotation->z = rot.z;
	invalidate();
}

void GameObject::updateRotation(glm::vec3 rot)
{
	rotation->x += rot.x;
	rotation->y += rot.y;
	rotation->z += rot.z;
	invalidate();
}

void GameObject::setScale(glm::vec3 scl)
{
	scale->x = scl.x;
	scale->y = scl.y;
	scale->z = scl.z;
	invalidate();
}

void GameObject::updateScale(glm::vec3 scl)
{
	scale->x += scl.x;
	scale->y += scl.y;
	scale->z += scl.z;
	invalidate();
}

void GameObject::setBasicTransforms() {
	tc->addScaleTransform(getScale());
	tc->addRotationTransform(getRotation());
	tc->addTranlateTransform(getPosition());
};

void GameObject::tick(float deltaTime)
{
	for (GameObject* child : childs) {
		child->tick(deltaTime);
	}
}

void GameObject::drawDebugElement()
{
	if (isGroup()) {
		ImGui::Begin("Object Debugger");
		std::string objectName(name);
		objectName += "GameObject (" + std::to_string((uintptr_t)this) + ")";
		if (ImGui::TreeNode(objectName.c_str())) {
			// position
			if (ImGui::DragFloat3("Position", glm::value_ptr(*position), 1, -100.0f, 100.0f)) {
				invalidate();
			}
			// rotation
			if (ImGui::DragFloat3("Rotation", glm::value_ptr(*rotation), 1, -100.0f, 100.0f)) {
				invalidate();
			}
			// scale
			if (ImGui::DragFloat3("Scale", glm::value_ptr(*scale), 1, -100.0f, 100.0f)) {
				invalidate();
			}
			for (GameObject* child : childs) {
				child->drawDebugElement();
			}
			ImGui::TreePop();
		}
		// End the window
		ImGui::End();
	}
	else {
		for (GameObject* child : childs) {
			child->drawDebugElement();
		}
	}
}

void GameObject::setId(GLuint id)
{
	objectId = id;
}

GLuint GameObject::getId()
{
	return objectId;
}

void GameObject::invalidate()
{
	for (GameObject* child : childs) {
		child->invalidate();
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
	child->parent = this;
	childs.emplace_back(child);
	child->tc->add(tc);
}