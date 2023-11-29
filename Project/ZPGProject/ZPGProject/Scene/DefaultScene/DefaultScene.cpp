#include "DefaultScene.h"

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
	meshManager.registerMesh("gift", Mesh(gift));
	meshManager.registerMesh("sphere", Mesh(sphere));
	meshManager.registerMesh("suziSmooth", Mesh(suziSmooth));
	meshManager.registerMesh("plain_indiced", Mesh(plain_indiced, plain_indices));

	models.push_back(GameObjectBuilder<HouseObjectGroup>()
		.setPosition(glm::vec3(.5f, 0, 0))
		.setScale(glm::vec3(.5f))
		.setBasicTransforms()
		.addChild(ModelBuilder()
			.name("firstModel")
			.setMesh(meshManager.getMesh("gift"))
			.setShader(shaderPrograms["firstShader"])
			.setPosition(glm::vec3(0, 0, 0))
			.setBasicTransforms()
			.finish())
		.addChild(ModelBuilder()
			.name("secondModel")
			.setMesh(meshManager.getMesh("plain_indiced"))
			.setShader(shaderPrograms["secondShader"])
			.setPosition(glm::vec3(0, 1, 0))
			.setBasicTransforms()
			.finish())
		.finish());

	models.push_back(ModelBuilder()
		.name("thirdModel")
		.setMesh(meshManager.getMesh("sphere"))
		.setShader(shaderPrograms[std::string("firstShader")])
		.setPosition(glm::vec3(-.5f, -.5f, 0))
		.setScale(glm::vec3(.3f))
		.setBasicTransforms()
		.finish());

	models.push_back(ModelBuilder()
		.name("fourthModel")
		.setMesh(meshManager.getMesh("suziSmooth"))
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
	Scene::draw();
}
