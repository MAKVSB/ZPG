#include "DefaultScene.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/GameObjectBuilder.h"

DefaultScene::DefaultScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void DefaultScene::createShaders()
{
	shaderPrograms["firstShader"] = ShaderBuilder()
		.name("firstShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_transformative.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_static.glsl")
		.compileAndCheck()
		->setCamera(camera);

	shaderPrograms["secondShader"] = ShaderBuilder()
		.name("secondShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_positional_color.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_positional.glsl")
		.compileAndCheck()
		->setCamera(camera);
}

void DefaultScene::createModels()
{	
	models.push_back(GameObjectBuilder<HouseObjectGroup>()
		.setPosition(glm::vec3(.5f, 0, 0))
		.setScale(glm::vec3(.5f))
		.setBasicTransforms()
		.addChild(ModelBuilder()
			.name("firstModel")
			.loadVertexesFromArray(cubeVertexData)
			.setShader(shaderPrograms["firstShader"])
			.setPosition(glm::vec3(0, 0, 0))
			.setBasicTransforms()
			.finish())
		.addChild(ModelBuilder()
			.name("secondModel")
			.loadVertexesFromArray(triangleVertexData)
			.setShader(shaderPrograms["secondShader"])
			.setPosition(glm::vec3(0, 1, 0))
			.setBasicTransforms()
			.finish())
		.finish());

	models.push_back(ModelBuilder()
		.name("thirdModel")
		.loadVertexesFromArray(sphere, POS3_NOR3)
		.setShader(shaderPrograms[std::string("firstShader")])
		.setPosition(glm::vec3(-.5f, -.5f, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());

	models.push_back(ModelBuilder()
		.name("fourthModel")
		.loadVertexesFromArray(suziSmooth, POS3_NOR3)
		.setShader(shaderPrograms[std::string("firstShader")])
		.setPosition(glm::vec3(-.5f, .5f, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());
}

void DefaultScene::tick(float deltaTime)
{
	Scene::tick(deltaTime);
	models[2]->getPosition()->x += deltaTime;
}

void DefaultScene::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
