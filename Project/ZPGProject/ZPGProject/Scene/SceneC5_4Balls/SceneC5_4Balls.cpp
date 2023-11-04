#include "SceneC5_4Balls.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/GameObjectBuilder.h"
#include "Light/Light.h"

SceneC5_4Balls::SceneC5_4Balls(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void SceneC5_4Balls::createShaders()
{
	shaderPrograms["lightShader0"] = ShaderBuilder()
		.name("lightShader0")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/constant.glsl")
		.compileAndCheck()
		->setCamera(camera);
	shaderPrograms["lightShader1"] = ShaderBuilder()
		.name("lightShader1")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/lambert.glsl")
		.compileAndCheck()
		->setCamera(camera);
	shaderPrograms["lightShader2"] = ShaderBuilder()
		.name("lightShader2")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	shaderPrograms["lightShader3"] = ShaderBuilder()
		.name("lightShader3")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/blinn.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["lightShader3"]);
	lightManager.attachShader(shaderPrograms["lightShader2"]);
	lightManager.attachShader(shaderPrograms["lightShader1"]);
}

void SceneC5_4Balls::createModels()
{
	modelManager.registerModel("sphere", ModelLoader::convertToVector(sphere));

	float distance = 0.7f;
	
	Light* light = new Light();
	light->setLightType(LightType::AMBIENT);
	light->setPosition(glm::vec3(0));
	light->setLightColor(glm::vec3(1, 1, 1));
	light->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	light->setLightStrength(32);
	models.push_back(light);

	Light* light2 = new Light();
	light2->setLightType(LightType::DIRECTIONAL);
	light2->setPosition(glm::vec3(0, 0, 0));
	light2->setLightDirection(glm::vec3(1, 0, 0));
	light2->setLightColor(glm::vec3(1, 1, 1));
	light2->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	light2->setLightStrength(32.0f);
	models.push_back(light2);

	Light* light3 = new Light();
	light3->setLightType(LightType::SPOTLIGHT);
	light3->setPosition(glm::vec3(0, 0, 0));
	light3->setLightDirection(glm::vec3(1, 0, 0));
	light3->setLightColor(glm::vec3(1, 1, 1));
	light3->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	light3->setLightStrength(32.0f);
	models.push_back(light3);

	Light* light4 = new Light();
	light4->setLightType(LightType::POINT);
	light4->setPosition(glm::vec3(0, 0, 0));
	light4->setLightDirection(glm::vec3(1, 0, 0));
	light4->setLightColor(glm::vec3(1, 1, 1));
	light4->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	light4->setLightStrength(32.0f);
	models.push_back(light4);

	models.push_back(ModelBuilder()
		.setVertexData(modelManager.getModel("sphere"))
		.setShader(shaderPrograms[std::string("lightShader3")])
		.setPosition(glm::vec3(0, distance, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
	models.push_back(ModelBuilder()
		.setVertexData(modelManager.getModel("sphere"))
		.setShader(shaderPrograms[std::string("lightShader3")])
		.setPosition(glm::vec3(distance, 0, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
	models.push_back(ModelBuilder()
		.setVertexData(modelManager.getModel("sphere"))
		.setShader(shaderPrograms[std::string("lightShader3")])
		.setPosition(glm::vec3(0, -distance, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
	models.push_back(ModelBuilder()
		.setVertexData(modelManager.getModel("sphere"))
		.setShader(shaderPrograms[std::string("lightShader3")])
		.setPosition(glm::vec3(-distance, 0, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
	models.push_back(ModelBuilder()
		.setVertexData(modelManager.getModel("sphere"))
		.setShader(shaderPrograms[std::string("lightShader3")])
		.setPosition(glm::vec3(-distance*3, 0, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());

	lightManager.updateLightReferences(models);
}

void SceneC5_4Balls::tick(float deltaTime)
{
	Scene::tick(deltaTime);
	for (GameObject* element : models) {
		if (!element->isCamera()) {
			element->getRotation()->x += 0.5f * deltaTime;
		}
	}
}

void SceneC5_4Balls::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
