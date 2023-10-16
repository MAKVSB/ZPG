#include "SceneC5.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/ModelBuilder.h"

SceneC5::SceneC5(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void SceneC5::createShaders()
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

void SceneC5::createModels()
{	
	float distance = 0.7f;
	models.push_back((new ModelBuilder())
		->loadVertexesFromArray(sphere, POS3_NOR3)
		->setShader(shaderPrograms[std::string("firstShader")])
		->setPosition(new glm::vec3(0, -distance, 0))
		->setScale(new glm::vec3(.3f))
		->setBasicTransforms()
		->finish());
	models.push_back((new ModelBuilder())
		->loadVertexesFromArray(sphere, POS3_NOR3)
		->setShader(shaderPrograms[std::string("firstShader")])
		->setPosition(new glm::vec3(0, distance, 0))
		->setScale(new glm::vec3(.3f))
		->setBasicTransforms()
		->finish());
	models.push_back((new ModelBuilder())
		->loadVertexesFromArray(sphere, POS3_NOR3)
		->setShader(shaderPrograms[std::string("firstShader")])
		->setPosition(new glm::vec3(distance, 0, 0))
		->setScale(new glm::vec3(.3f))
		->setBasicTransforms()
		->finish());
	models.push_back((new ModelBuilder())
		->loadVertexesFromArray(sphere, POS3_NOR3)
		->setShader(shaderPrograms[std::string("firstShader")])
		->setPosition(new glm::vec3(-distance, 0, 0))
		->setScale(new glm::vec3(.3f))
		->setBasicTransforms()
		->finish());
}

void SceneC5::tick(double deltaTime)
{
	Scene::tick(deltaTime);
}

void SceneC5::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
