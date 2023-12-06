#include "Scene.h"

Scene::Scene(GLFWwindow* wndw) {
	window = wndw;
	createShaders();
	createModels();
	camera = new Camera(window);
	models.push_back(camera);

	indexUsageMap[0] = true;
};

Scene::~Scene() {
	for (auto sp : shaderPrograms) {
		delete sp.second;
	}
	for (auto model : models) {
		delete model;
	}
};

void Scene::createShaders() {
};
void Scene::createModels() {
};

void Scene::tick(float deltaTime) {
	for (GameObject* element : models) {
		element->tick(deltaTime);
	}
};

void Scene::draw() {
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	for (GameObject* element : models) {
		element->draw();
	}
}

void Scene::drawDebugElement() {
	for (GameObject* element : models) {
		element->drawDebugElement();
	}
}

bool Scene::matchWithWildcard(const std::string& pattern, const std::string& text) {
	std::string regexPattern = std::regex_replace(pattern, std::regex("\\*"), ".*");
	return std::regex_match(text, std::regex(regexPattern));
}

GameObject* Scene::getGameObjectByIndexRecursive(std::vector<GameObject*> mdls, int index, std::string nameFilterPattern)
{
	for (GameObject* object : mdls) {
		if (!object->childs.empty()) {
			GameObject* retObj = getGameObjectByIndexRecursive(object->childs, index, nameFilterPattern);
			if (retObj != nullptr) {
				return retObj;
			}
		}
			
		if (object->getId() == index && (nameFilterPattern == "" || matchWithWildcard(nameFilterPattern, object->name))) {
			return object;
		}
	}
	return nullptr;
}

GameObject* Scene::getGameObjectByIndex(int index, std::string nameFilterPattern)
{
	return getGameObjectByIndexRecursive(models, index, nameFilterPattern);
}

int Scene::getUnusedIndex(int min, int max)
{
	for (int i = min; i <= max; i++) {
		if (!indexUsageMap[i]) {
			return i;
		}
	}

	return -1;
}
