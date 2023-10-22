#include "SceneManager.h"

// fuck this stupid c++ without reflexion. Its impossible to make any non-static factory because c++ sucks
SceneManager::SceneManager(GLFWwindow* wndw) {
	window = wndw;
	CallbackManager::getInstance()->add(this);
}

void SceneManager::registerScene(std::type_index type, std::string name, std::string desc)
{
	SceneStruct sceneData = { type, name, desc };
	scenes.emplace_back(sceneData);
}

void SceneManager::registerScenes()
{
	registerScene(std::type_index(typeid(DefaultScene)), "Default scene", "Default scene");
	registerScene(std::type_index(typeid(SceneC5)), "4 Balls with light", "Vytvoøeno na pátem cvièení k light shaderu");
}

void SceneManager::printSceneMenu() {
	int i = 1;
	for (auto scn : scenes) {
		printf("%d: %s (%s)\n", i, scn.name.c_str(), scn.desc.c_str());
		i++;
	}
}

int SceneManager::getSceneValue() {
	int value;
	scanf_s("%d", &value);
	while (value > scenes.size()) {
		printf("Invalid scene");
		scanf_s("%d", &value);
	}
	return value;
}

void SceneManager::listen(MessageType messageType, void* object)
{
	if (messageType == MessageType::KeyPressed) {
		CallbackManager::CBKeyData* data =  static_cast<CallbackManager::CBKeyData*>(object);
		if (data->key == GLFW_KEY_O) {
			printSceneMenu();
		}
	}
}

Scene* SceneManager::sceneSelector()
{
	glfwHideWindow(window);
	printSceneMenu();
	int value = getSceneValue()-1;
	glfwShowWindow(window);
	glfwSetTime(0.0);
	if (scenes[value].type == std::type_index(typeid(DefaultScene))) {
		return SceneFactory<DefaultScene>().create(window);
	} else if (scenes[value].type == std::type_index(typeid(SceneC5))) {
		return SceneFactory<SceneC5>().create(window);
	} else {
		return SceneFactory<DefaultScene>().create(window);
	}
}
