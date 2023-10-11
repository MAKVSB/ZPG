#include "DefaultScene.h"

#include "CallbackManager.h"

int yDir = 0;
int xDir = 0;

void DefaultScene::listen(MessageType mt, void* data)
{
	if (mt == MessageType::KeyPressed || mt == MessageType::KeyHeld) {
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
		//if (dataStruct->key == GLFW_KEY_SPACE) {
		//	yDir = 0;
		//	xDir = 0;
		//}
	}
}

DefaultScene::DefaultScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
	CallbackManager::getInstance()->add(this);
}

void DefaultScene::createShaders()
{
	shaderPrograms[std::string("firstShader")] = (new ShaderBuilder())
		->name("firstShader")
		->addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_transformative.glsl")
		->addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_static.glsl")
		->compileAndCheck()
		->setCamera(camera);

	shaderPrograms[std::string("secondShader")] = (new ShaderBuilder())
		->name("secondShader")
		->addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_positional_color.glsl")
		->addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_positional.glsl")
		->compileAndCheck()
		->setCamera(camera);
}

void DefaultScene::createModels()
{	
	Model* firstModel = new Model(ModelLoader::convertToVector<float>(cubeVertexData));
	firstModel->shader = shaderPrograms[std::string("firstShader")];
	firstModel->positionRelToWorld = new glm::vec3(.5f, 0, 0);
	firstModel->positionRelToCenter = new glm::vec3(0, -.25f, 0);
	firstModel->scale = new glm::vec3(.5f);
	firstModel->tc->addTranlateTransform(firstModel->positionRelToWorld); //move to the world
	firstModel->tc->addRotationTransform(firstModel->rotationRelToCenter); //rotate on place
	firstModel->tc->addTranlateTransform(firstModel->positionRelToCenter); //move relative to its center (when building object from multiple objects)
	firstModel->tc->addScaleTransform(firstModel->scale); // scale down
	models.push_back(firstModel);

	Model* secondModel = new Model(ModelLoader::convertToVector<float>(triangleVertexData));
	secondModel->shader = shaderPrograms[std::string("firstShader")];
	secondModel->positionRelToWorld = new glm::vec3(.5f, 0, 0);
	secondModel->positionRelToCenter = new glm::vec3(0, .25f, 0);
	secondModel->scale = new glm::vec3(.5f);
	secondModel->tc->addTranlateTransform(secondModel->positionRelToWorld);
	secondModel->tc->addRotationTransform(secondModel->rotationRelToCenter);
	secondModel->tc->addTranlateTransform(secondModel->positionRelToCenter);
	secondModel->tc->addScaleTransform(secondModel->scale);
	models.push_back(secondModel);

	Model* thirdModel = new Model(ModelLoader::convertToVector<float>(sphere), POS3_NOR3);
	thirdModel->shader = shaderPrograms[std::string("firstShader")];
	thirdModel->positionRelToWorld = new glm::vec3(-.5f, -.5f, 0);
	thirdModel->scale = new glm::vec3(.3f);
	thirdModel->tc->addTranlateTransform(thirdModel->positionRelToWorld);
	thirdModel->tc->addScaleTransform(thirdModel->scale);
	models.push_back(thirdModel);

	Model* forthModel = new Model(ModelLoader::convertToVector<float>(suziSmooth), POS3_NOR3);
	forthModel->shader = shaderPrograms[std::string("firstShader")];
	forthModel->positionRelToWorld = new glm::vec3(-.5f, .5f, 0);
	forthModel->scale = new glm::vec3(.3f);
	forthModel->tc->addTranlateTransform(forthModel->positionRelToWorld);
	forthModel->tc->addScaleTransform(forthModel->scale);
	models.push_back(forthModel);
}

void DefaultScene::tick(double deltaTime)
{
	camera->tick(deltaTime);
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (Model* element : models) {
		element->rotationRelToCenter->y += (float)deltaTime * yDir;
		element->rotationRelToCenter->x += (float)deltaTime * .5f * xDir;
		element->draw();
	}
}
