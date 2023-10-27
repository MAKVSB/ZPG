#include <CallbackManager.h>
#include <Observer.h>
#include <vector>
#include <typeindex>
#include <memory>

#include "Scene/DefaultScene/DefaultScene.h"
#include "Scene/SceneC5_4Balls/SceneC5_4Balls.h"
#include "Scene/SceneC5_1Ball/SceneC5_1Ball.h"
#include "Scene/SceneC5_4Objects/SceneC5_4Objects.h"
#include "Scene/ForestScene/ForestScene.h"
#include "Scene/Universe/Universe.h"

class SceneManager: public Observer {
private:
	struct SceneStruct {
		std::type_index type;
		std::string name;
		std::string desc;
	};
	GLFWwindow* window;

	std::vector<SceneStruct> scenes;

	void printSceneMenu();
	int getSceneValue();
public:
	SceneManager(GLFWwindow* wndw);

	void registerScene(std::type_index type, std::string name, std::string desc);
	void registerScenes();
	Scene* sceneSelector();

	void listen(MessageType messageType, void* object);
};