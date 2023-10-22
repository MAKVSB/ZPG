#include "ForestScene.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/GameObjectBuilder.h"
#include "Light/Light.h"

ForestScene::ForestScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void ForestScene::createShaders()
{
	shaderPrograms["lightShader"] = ShaderBuilder()
		.name("lightShader2")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
}

void ForestScene::createModels()
{
	float distance = 0.7f;

	Light* light = new Light();
	light->setPosition(glm::vec3(0));

	camera->setPosition(glm::vec3(0, 1, 2));

	int terrainSize = 5;

	for (int i = -terrainSize; i < terrainSize;i++) {
		for (int j = -terrainSize; j < terrainSize;j++) {
			models.push_back(ModelBuilder()
				.loadVertexesFromArray(plain, POS3_NOR3)
				.setShader(shaderPrograms[std::string("lightShader")])
				.setPosition(glm::vec3(i * 2, -1, j * 2))
				.setBasicTransforms()
				.finish());
		}
	}

	models.push_back(ModelBuilder()
		.loadVertexesFromArray(tree, POS3_NOR3)
		.setShader(shaderPrograms[std::string("lightShader")])
		.setPosition(glm::vec3(1, -1, 1))
		.setBasicTransforms()
		.finish());
}

void ForestScene::tick(double deltaTime)
{
	Scene::tick(deltaTime);
}

void ForestScene::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
