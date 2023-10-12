#include "DefaultScene.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/ModelBuilder.h"

DefaultScene::DefaultScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void DefaultScene::createShaders()
{
	shaderPrograms["firstShader"] = (new ShaderBuilder())
		->name("firstShader")
		->addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_transformative.glsl")
		->addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_static.glsl")
		->compileAndCheck()
		->setCamera(camera);

	shaderPrograms["secondShader"] = (new ShaderBuilder())
		->name("secondShader")
		->addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_positional_color.glsl")
		->addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_positional.glsl")
		->compileAndCheck()
		->setCamera(camera);
}

void DefaultScene::createModels()
{	
	models.push_back((new GameObjectBuilder<HouseObjectGroup>())
		->setPosition(new glm::vec3(.5f, 0, 0))
		->setScale(new glm::vec3(.5f))
		->setBasicTransforms()
		->addChild((new ModelBuilder())
			->loadVertexesFromArray(cubeVertexData)
			->setShader(shaderPrograms["firstShader"])
			->name("firstModel") // little bit unwanted behaviour -> once GameObjectBuilder method is used, ModelBuilder specific methods are no longer available
			->setPosition(new glm::vec3(0, -.5f, 0))
			->setBasicTransforms()
			->finish())
		->addChild((new ModelBuilder())
			->loadVertexesFromArray(triangleVertexData)
			->setShader(shaderPrograms["secondShader"])
			->setPosition(new glm::vec3(0, .5f, 0))
			->setBasicTransforms()
			->finish())
		->finish());

	models.push_back((new ModelBuilder())
		->loadVertexesFromArray(sphere, POS3_NOR3)
		->setShader(shaderPrograms[std::string("firstShader")])
		->setPosition(new glm::vec3(-.5f, -.5f, 0))
		->setScale(new glm::vec3(.3f))
		->setBasicTransforms()
		->finish());

	models.push_back((new ModelBuilder())
		->loadVertexesFromArray(suziSmooth, POS3_NOR3)
		->setShader(shaderPrograms[std::string("firstShader")])
		->setPosition(new glm::vec3(-.5f, .5f, 0))
		->setScale(new glm::vec3(.3f))
		->setBasicTransforms()
		->finish());
}

void DefaultScene::tick(double deltaTime)
{
	for (GameObject* element : models) {
		element->tick(deltaTime);
	}
}

void DefaultScene::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (GameObject* element : models) {
		element->draw();
	}
}
