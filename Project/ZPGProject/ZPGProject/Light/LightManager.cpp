#include "LightManager.h"

LightManager::LightManager()
{
	lightsUBO = 0;
	glGenBuffers(1, &lightsUBO);
	glBindBuffer(GL_UNIFORM_BUFFER, lightsUBO);
	glBufferData(GL_UNIFORM_BUFFER, (sizeof(LightStruct) * MAX_LIGHTS)+16, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

LightManager::~LightManager()
{
	glDeleteBuffers(1, &lightsUBO);
}

void LightManager::attachShader(ShaderProgram* sp)
{
	shaders.push_back(sp);
	sp->bindUniformObject("LightArray", lightsUBO, sizeof(LightStruct) * MAX_LIGHTS);
}

void LightManager::updateLightReferences(std::vector<GameObject*> gameObjects) {
	lights.clear();
	updateLightReferencesRecursive(gameObjects);
}

void LightManager::updateLightReferencesRecursive(std::vector<GameObject*> gameObjects)
{
	for (GameObject* object : gameObjects) {
		if (!object->childs.empty()) updateLightReferencesRecursive(object->childs);
		if (object->isLight()) {
			lights.emplace_back(static_cast<Light*>(object));
		}
	}
	for (Light* light : lights) {
		light->add(this);
		listen(MessageType::LightChanged, light);
	}
}

void LightManager::listen(MessageType messageType, void* target)
{
	if (messageType == MessageType::LightChanged) {
		auto it = std::find(lights.begin(), lights.end(), target);

		if (it != lights.end()) {
			int index = (int)std::distance(lights.begin(), it);
			float lightSize = static_cast<float>(lights.size());
			LightStruct ls = static_cast<Light*>(target)->getStruct();
			ShaderProgram::uploadUniformObject(lightsUBO, sizeof(float), &lightSize, 0);
			ShaderProgram::uploadUniformObject(lightsUBO, sizeof(LightStruct), &ls, (80 * index)+16);
		}
	}
}
