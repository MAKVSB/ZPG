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
	registerScene(std::type_index(typeid(SceneC5_4Balls)), "4 Balls with light in middle", "Vytvoøeno na cvièení k light shaderu");
	registerScene(std::type_index(typeid(SceneC5_4Objects)), "4 Objects with light in middle", "Vytvoøeno na cvièení k light shaderu");
	registerScene(std::type_index(typeid(SceneC5_1Ball)), "1 Balls with light beihnd", "Vytvoøeno na cvièení k light shaderu");
	registerScene(std::type_index(typeid(ForestScene)), "Forest scene", "");
	registerScene(std::type_index(typeid(UniverseScene)), "Universe", "");
	registerScene(std::type_index(typeid(AssimpLoaderScene)), "AssimpLoaderScene", "");
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
		return new DefaultScene(window);
	} else if (scenes[value].type == std::type_index(typeid(SceneC5_4Balls))) {
		return new SceneC5_4Balls(window);
	} else if (scenes[value].type == std::type_index(typeid(SceneC5_4Objects))) {
		return new SceneC5_4Objects(window);
	} else if (scenes[value].type == std::type_index(typeid(SceneC5_1Ball))) {
		return new SceneC5_1Ball(window);
	} else if (scenes[value].type == std::type_index(typeid(ForestScene))) {
		return new ForestScene(window);
	} else if (scenes[value].type == std::type_index(typeid(UniverseScene))) {
		return new UniverseScene(window);
	} else if (scenes[value].type == std::type_index(typeid(AssimpLoaderScene))) {
		return new AssimpLoaderScene(window);
	} else {
		return new DefaultScene(window);
	}
}
