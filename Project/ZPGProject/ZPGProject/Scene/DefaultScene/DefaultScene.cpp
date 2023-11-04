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
	modelManager.registerModel("gift", ModelLoader::convertToVector(gift));
	modelManager.registerModel("sphere", ModelLoader::convertToVector(sphere));
	modelManager.registerModel("suziSmooth", ModelLoader::convertToVector(suziSmooth));

	models.push_back(GameObjectBuilder<HouseObjectGroup>()
		.setPosition(glm::vec3(.5f, 0, 0))
		.setScale(glm::vec3(.5f))
		.setBasicTransforms()
		.addChild(ModelBuilder()
			.name("firstModel")
			.setVertexData(modelManager.getModel("gift"))
			.setShader(shaderPrograms["firstShader"])
			.setPosition(glm::vec3(0, 0, 0))
			.setBasicTransforms()
			.finish())
		.addChild(ModelBuilder()
			.name("secondModel")
			.setVertexData(modelManager.getModel("sphere"))
			.setShader(shaderPrograms["secondShader"])
			.setPosition(glm::vec3(0, 1, 0))
			.setScale(glm::vec3(0.2))
			.setBasicTransforms()
			.finish())
		.finish());

	models.push_back(ModelBuilder()
		.name("thirdModel")
		.setVertexData(modelManager.getModel("sphere"))
		.setShader(shaderPrograms[std::string("firstShader")])
		.setPosition(glm::vec3(-.5f, -.5f, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());

	models.push_back(ModelBuilder()
		.name("fourthModel")
		.setVertexData(modelManager.getModel("suziSmooth"))
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
