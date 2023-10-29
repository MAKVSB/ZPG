#include "SceneC5_1Ball.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/GameObjectBuilder.h"
#include "Light/Light.h"

SceneC5_1Ball::SceneC5_1Ball(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void SceneC5_1Ball::createShaders()
{
	shaderPrograms["lightShader"] = ShaderBuilder()
		.name("lightShader2")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
}

void SceneC5_1Ball::createModels()
{
	modelManager.registerModel("sphere", ModelLoader::convertToVector(suziSmooth));

	float distance = 0.7f;
	
	//Light* light = new Light();
	//light->setPosition(glm::vec3(0));
	//models.push_back(light);

	camera->setPosition(glm::vec3(0, 0, 2));


	models.push_back(ModelBuilder()
		.setVertexData(modelManager.getModel("sphere"))
		.setShader(shaderPrograms[std::string("lightShader")])
		.setPosition(glm::vec3(0, 0, distance))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
}

void SceneC5_1Ball::tick(float deltaTime)
{
	Scene::tick(deltaTime);
	for (GameObject* element : models) {
		if (!element->isCamera()) {
			element->getRotation()->x += 0.5f * deltaTime;
		}
	}
}

void SceneC5_1Ball::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
