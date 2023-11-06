#include "AssimpLoaderScene.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/GameObjectBuilder.h"
#include "Light/Light.h"

AssimpLoaderScene::AssimpLoaderScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void AssimpLoaderScene::createShaders()
{
	shaderPrograms["lightShader"] = ShaderBuilder()
		.name("lightShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["lightShader"]);
}

void AssimpLoaderScene::createModels()
{
	meshManager.registerMesh("sphere", sphere);

	Light* light = new Light();
	light->setLightType(LightType::AMBIENT);
	light->setPosition(glm::vec3(0));
	light->setLightColor(glm::vec3(1, 1, 1));
	light->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	light->setLightStrength(32);
	models.push_back(light);

	Light* light4 = new Light();
	light4->setLightType(LightType::POINT);
	light4->setPosition(glm::vec3(0, 0, 0));
	light4->setLightDirection(glm::vec3(1, 0, 0));
	light4->setLightColor(glm::vec3(1, 1, 1));
	light4->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	light4->setLightStrength(32.0f);
	models.push_back(light4);

	ModelLoader ml = ModelLoader(&meshManager);
	GameObject* loadedModel = ml.loadModel("C:/Users/mdani/Downloads/Bambo_House.obj");
	applyLoadedModelSettings(loadedModel, shaderPrograms);
	models.push_back(loadedModel);

	models.push_back(ModelBuilder()
		.setMesh(meshManager.getMesh("sphere"))
		.setShader(shaderPrograms[std::string("lightShader")])
		.setBasicTransforms()
		.finish());

	lightManager.updateLightReferences(models);
}

void AssimpLoaderScene::applyLoadedModelSettings(GameObject* go, std::map<std::string, ShaderProgram*> shaderPrograms) {
	Model* gomdl = dynamic_cast<Model*>(go);
	if (gomdl != nullptr) {
		gomdl->setShader(shaderPrograms[std::string("lightShader")]);
	}
	if (go != nullptr) {
		go->tc->addRotationTransform(go->getRotation());
		go->tc->addTranlateTransform(go->getPosition());
		go->tc->addScaleTransform(go->getScale());
		for (GameObject* child : go->childs) {
			applyLoadedModelSettings(child, shaderPrograms);
		}
	}
}

void AssimpLoaderScene::tick(float deltaTime)
{
	Scene::tick(deltaTime);
	((Light*)models[2])->setPosition(*camera->getPosition());
	//for (GameObject* element : models) {
	//	if (!element->isCamera()) {
	//		element->updateRotation(glm::vec3(0.1f * deltaTime, 0, 0));
	//	}
	//}
}

void AssimpLoaderScene::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
