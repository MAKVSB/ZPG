#include "HouseObjectGroup.h"
#include <CallbackManager.h>

void HouseObjectGroup::tick(double deltaTime)
{
	GameObject::tick(deltaTime);
	rotation->y += (float)deltaTime * yDir;
	rotation->x += (float)deltaTime * .5f * xDir;
}

void HouseObjectGroup::draw()
{
	GameObject::draw();
}

void HouseObjectGroup::listen(MessageType messageType, void* object)
{
	if (messageType == MessageType::KeyPressed || messageType == MessageType::KeyHeld) {
		CallbackManager::CBKeyData* dataStruct = static_cast<CallbackManager::CBKeyData*>(object);
		if (dataStruct->key == GLFW_KEY_UP) {
			xDir = -1;
		}
		if (dataStruct->key == GLFW_KEY_DOWN) {
			xDir = 1;
		}
		if (dataStruct->key == GLFW_KEY_LEFT) {
			yDir = -1;
		}
		if (dataStruct->key == GLFW_KEY_RIGHT) {
			yDir = 1;
		}
		if (dataStruct->key == GLFW_KEY_SPACE) {
			yDir = 0;
			xDir = 0;
		}
	}
}

HouseObjectGroup::HouseObjectGroup() {
	CallbackManager::getInstance()->add(this);
}
HouseObjectGroup::~HouseObjectGroup() {
	CallbackManager::getInstance()->remove(this);
}