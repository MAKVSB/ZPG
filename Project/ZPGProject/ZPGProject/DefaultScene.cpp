#include "DefaultScene.h"

DefaultScene::DefaultScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void DefaultScene::createShaders()
{
	ShaderProgram* firstShader = new ShaderProgram();
	firstShader->addShader(GL_VERTEX_SHADER, "vertex_shader.glsl");
	firstShader->addShader(GL_FRAGMENT_SHADER, "fragment_shader_color_static.glsl");
	firstShader->compile();
	firstShader->check();
	shaderPrograms[std::string("firstShader")] = firstShader;

	ShaderProgram* secondShader = new ShaderProgram();
	secondShader->addShader(GL_VERTEX_SHADER, "vertex_shader_positional_color.glsl");
	secondShader->addShader(GL_FRAGMENT_SHADER, "fragment_shader_color_positional.glsl");
	secondShader->compile();
	secondShader->check();
	shaderPrograms[std::string("secondShader")] = secondShader;
}

void DefaultScene::createModels()
{
	Model* firstModel = new Model(cubeVertexData);
	firstModel->position = glm::vec3(0, -.1f, 0);
	firstModel->scale = glm::vec3(.5f);
	firstModel->shader = shaderPrograms[std::string("firstShader")];
	models.push_back(firstModel);

	Model* secondModel = new Model(triangleVertexData);
	secondModel->position = glm::vec3(0, .4f, 0);
	secondModel->scale = glm::vec3(.5f);
	secondModel->shader = shaderPrograms[std::string("secondShader")];
	models.push_back(secondModel);
}

void DefaultScene::tick(double deltaTime)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Model* element : models) {
		element->rotation[1] += deltaTime;
		element->rotation[0] += deltaTime*.5f;
		element->draw();
	}
	// update other events like input handling
	glfwPollEvents();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}
