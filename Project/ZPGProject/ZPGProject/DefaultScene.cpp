#include "DefaultScene.h"

#include "CallbackManager.h"

int yDir = 0;
int xDir = 0;

void keyPressedObserver(MessageType mt, void* data) {
	CallbackManager::CBKeyData* dataStruct = static_cast<CallbackManager::CBKeyData*>(data);
	if (mt != MessageType::KeyPressed) return;
	if (dataStruct->key == GLFW_KEY_W) {
		xDir = 1;
	}
	if (dataStruct->key == GLFW_KEY_S) {
		xDir = -1;
	}
	if (dataStruct->key == GLFW_KEY_A) {
		yDir = 1;
	}
	if (dataStruct->key == GLFW_KEY_D) {
		yDir = -1;
	}
	if (dataStruct->key == GLFW_KEY_SPACE) {
		yDir = 0;
		xDir = 0;
	}
};

DefaultScene::DefaultScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
	CallbackManager* cbm = new CallbackManager(window);
	cbm->add(keyPressedObserver);


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
	firstModel->position = new glm::vec3(0, -.5f, 0);
	firstModel->scale = new glm::vec3(.5f);
	firstModel->shader = shaderPrograms[std::string("firstShader")];
	firstModel->tc->addScaleTransform(firstModel->scale);
	firstModel->tc->addRotationTransform(firstModel->rotation);
	firstModel->tc->addTranlateTransform(firstModel->position);
	models.push_back(firstModel);

	Model* secondModel = new Model(triangleVertexData);
	secondModel->position = new glm::vec3(0, .5f, 1);
	secondModel->scale = new glm::vec3(.5f);
	secondModel->shader = shaderPrograms[std::string("secondShader")];
	secondModel->tc->addScaleTransform(secondModel->scale);
	secondModel->tc->addRotationTransform(secondModel->rotation);
	secondModel->tc->addTranlateTransform(secondModel->position);
	models.push_back(secondModel);
}

void DefaultScene::tick(double deltaTime)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Model* element : models) {
		element->rotation->y += (float)deltaTime * yDir;
		element->rotation->x += (float)deltaTime * .5f * xDir;
		element->draw();
	}
	// update other events like input handling
	glfwPollEvents();
	// put the stuff we’ve been drawing onto the display
	glfwSwapBuffers(window);
}
