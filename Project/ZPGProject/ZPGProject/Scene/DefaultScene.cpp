#include "DefaultScene.h"

#include "CallbackManager.h"

int yDir = 0;
int xDir = 0;


void DefaultScene::listen(MessageType mt, void* data)
{
	if (mt != MessageType::KeyPressed) return;
	CallbackManager::CBKeyData* dataStruct = static_cast<CallbackManager::CBKeyData*>(data);
	if (dataStruct->key == GLFW_KEY_UP) {
		xDir = 1;
	}
	if (dataStruct->key == GLFW_KEY_DOWN) {
		xDir = -1;
	}
	if (dataStruct->key == GLFW_KEY_LEFT) {
		yDir = 1;
	}
	if (dataStruct->key == GLFW_KEY_RIGHT) {
		yDir = -1;
	}
	if (dataStruct->key == GLFW_KEY_SPACE) {
		yDir = 0;
		xDir = 0;
	}
}

DefaultScene::DefaultScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
	CallbackManager::getInstance()->add(this);
}

void DefaultScene::createShaders()
{
	ShaderProgram* firstShader = new ShaderProgram();
	firstShader->addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader.glsl");
	firstShader->addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_static.glsl");
	firstShader->compile();
	firstShader->check();
	shaderPrograms[std::string("firstShader")] = firstShader;

	ShaderProgram* secondShader = new ShaderProgram();
	secondShader->addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_positional_color.glsl");
	secondShader->addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_positional.glsl");
	secondShader->compile();
	secondShader->check();
	shaderPrograms[std::string("secondShader")] = secondShader;
}

void DefaultScene::createModels()
{
	Model* firstModel = new Model(cubeVertexData);
	firstModel->positionRelToWorld = new glm::vec3(.5f, 0, 0);
	firstModel->positionRelToCenter = new glm::vec3(0, -.25f, 0);
	firstModel->scale = new glm::vec3(.5f);
	firstModel->shader = shaderPrograms[std::string("firstShader")];
	firstModel->tc->addTranlateTransform(firstModel->positionRelToWorld); //move to the world
	firstModel->tc->addRotationTransform(firstModel->rotationRelToCenter); //rotate on place
	firstModel->tc->addTranlateTransform(firstModel->positionRelToCenter); //move relative to its center (when building object from multiple objects)
	firstModel->tc->addScaleTransform(firstModel->scale); // scale down
	models.push_back(firstModel);

	Model* secondModel = new Model(triangleVertexData);
	secondModel->positionRelToWorld = new glm::vec3(.5f, 0, 0);
	secondModel->positionRelToCenter = new glm::vec3(0, .25f, 0);
	secondModel->scale = new glm::vec3(.5f);
	secondModel->shader = shaderPrograms[std::string("secondShader")];
	secondModel->tc->addTranlateTransform(secondModel->positionRelToWorld);
	secondModel->tc->addRotationTransform(secondModel->rotationRelToCenter);
	secondModel->tc->addTranlateTransform(secondModel->positionRelToCenter);
	secondModel->tc->addScaleTransform(secondModel->scale);
	models.push_back(secondModel);

	Model* thirdModel = new Model(sphere, POS3_NOR3);
	thirdModel->positionRelToWorld = new glm::vec3(-.5f, -.5f, 0);
	thirdModel->scale = new glm::vec3(.2f);
	thirdModel->shader = shaderPrograms[std::string("secondShader")];
	thirdModel->tc->addTranlateTransform(thirdModel->positionRelToWorld);
	thirdModel->tc->addRotationTransform(thirdModel->rotationRelToCenter);
	thirdModel->tc->addScaleTransform(thirdModel->scale);
	models.push_back(thirdModel);

	Model* forthModel = new Model(suziSmooth, POS3_NOR3);
	forthModel->positionRelToWorld = new glm::vec3(-.5f, .5f, 0);
	forthModel->scale = new glm::vec3(.2f);
	forthModel->shader = shaderPrograms[std::string("firstShader")];
	forthModel->tc->addTranlateTransform(forthModel->positionRelToWorld);
	forthModel->tc->addRotationTransform(forthModel->rotationRelToCenter);
	forthModel->tc->addScaleTransform(forthModel->scale);
	models.push_back(forthModel);
}

void DefaultScene::tick(double deltaTime)
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for (Model* element : models) {
		element->rotationRelToCenter->y += (float)deltaTime * yDir;
		element->rotationRelToCenter->x += (float)deltaTime * .5f * xDir;
		element->draw();
	}
}
