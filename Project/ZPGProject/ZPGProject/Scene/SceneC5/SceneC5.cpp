#include "SceneC5.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/GameObjectBuilder.h"
#include "Light/Light.h"

SceneC5::SceneC5(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void SceneC5::createShaders()
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
		.name("lightShader2")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/blinn.glsl")
		.compileAndCheck()
		->setCamera(camera);
}

void SceneC5::createModels()
{
	float distance = 0.7f;
	
	//Light* light = new Light();
	//light->setPosition(glm::vec3(0));
	//models.push_back(light);

	models.push_back(ModelBuilder()
		.loadVertexesFromArray(suziSmooth, POS3_NOR3)
		.setShader(shaderPrograms[std::string("lightShader0")])
		.setPosition(glm::vec3(0, distance, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
	models.push_back(ModelBuilder()
		.loadVertexesFromArray(suziSmooth, POS3_NOR3)
		.setShader(shaderPrograms[std::string("lightShader1")])
		.setPosition(glm::vec3(distance, 0, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
	models.push_back(ModelBuilder()
		.loadVertexesFromArray(suziSmooth, POS3_NOR3)
		.setShader(shaderPrograms[std::string("lightShader2")])
		.setPosition(glm::vec3(0, -distance, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
	models.push_back(ModelBuilder()
		.loadVertexesFromArray(suziSmooth, POS3_NOR3)
		.setShader(shaderPrograms[std::string("lightShader3")])
		.setPosition(glm::vec3(-distance, 0, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
	models.push_back(ModelBuilder()
		.loadVertexesFromArray(suziSmooth, POS3_NOR3)
		.setShader(shaderPrograms[std::string("lightShader3")])
		.setPosition(glm::vec3(-distance*3, 0, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
}

void SceneC5::tick(double deltaTime)
{
	Scene::tick(deltaTime);
	for (GameObject* element : models) {
		if (element != camera) {
			element->getRotation()->x += 0.5 * deltaTime;
		}
	}
}

void SceneC5::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
