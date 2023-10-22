#include "HouseObjectGroup.h"
#include <CallbackManager.h>

void HouseObjectGroup::tick(double deltaTime)
{
	GameObject::tick(deltaTime);
	if ((*keypressMap)[GLFW_KEY_UP] > 0) {
		rotation->x += (float)deltaTime;
	}
	if ((*keypressMap)[GLFW_KEY_DOWN] > 0) {
		rotation->x -= (float)deltaTime;
	}
	if ((*keypressMap)[GLFW_KEY_LEFT] > 0) {
		rotation->y -= (float)deltaTime;
	}
	if ((*keypressMap)[GLFW_KEY_RIGHT] > 0) {
		rotation->y += (float)deltaTime;
	}
}

void HouseObjectGroup::draw()
{
	GameObject::draw();
}

void HouseObjectGroup::listen(MessageType messageType, void* object)
{
	if (messageType == MessageType::KeyPressed || messageType == MessageType::KeyHeld) {
		CallbackManager::CBKeyData* dataStruct = static_cast<CallbackManager::CBKeyData*>(object);
		keypressMap = dataStruct->map;
	}
}

HouseObjectGroup::HouseObjectGroup() {
	CallbackManager::getInstance()->add(this);
}
HouseObjectGroup::~HouseObjectGroup() {
	printf("deleting HOG");
	CallbackManager::getInstance()->remove(this);
}