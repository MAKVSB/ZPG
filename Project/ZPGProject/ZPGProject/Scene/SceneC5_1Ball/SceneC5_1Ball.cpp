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
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/blinn.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["lightShader"]);
}

void SceneC5_1Ball::createModels()
{
	meshManager.registerMesh("sphere", sphere);

	float distance = 0.7f;
	
	Light* light = new Light();
	light->setPosition(glm::vec3(0, 0, -2));
	//light->setLightAttenuation(glm::vec3(1, 2, 2));
	models.push_back(light);

	camera->setPosition(glm::vec3(0, 0, 2));

	Material m;
	m.r_a = glm::vec4(0.5, 0.5, 0.5, 0);
	m.r_d = glm::vec4(0.5, 0.5, 0.5, 0);
	m.r_s = glm::vec4(10, 10, 10, 0);

	models.push_back(ModelBuilder()
		.setMesh(meshManager.getMesh("sphere"))
		.setShader(shaderPrograms[std::string("lightShader")])
		.setPosition(glm::vec3(0, 0, distance))
		.setScale(glm::vec3(.3f))
		.setMaterial(m)
		.setBasicTransforms()
		.finish());

	lightManager.updateLightReferences(models);
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
