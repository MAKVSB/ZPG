#include "Universe.h"

#include "CallbackManager.h"

#include "Scene/DefaultScene/HouseObjectGroup.h"
#include "Model/GameObjectBuilder.h"
#include "Light/Light.h"
#include "OffsetRotator.h"

UniverseScene::UniverseScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void UniverseScene::createShaders()
{
	shaderPrograms["lightShader"] = ShaderBuilder()
		.name("lightShader0")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/constant.glsl")
		.compileAndCheck()
		->setCamera(camera);
	shaderPrograms["secondShader"] = ShaderBuilder()
		.name("secondShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_positional_color.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_positional.glsl")
		.compileAndCheck()
		->setCamera(camera);
}

glm::vec3 globalscale = glm::vec3(0.5f);

glm::vec3 sunRotationInner = glm::vec3(0);
glm::vec3 sunScale = glm::vec3(.5f);

glm::vec3 mercurOffset = glm::vec3(2.5, 0, 0);
glm::vec3 mercurRotation = glm::vec3(0);
glm::vec3 mercurRotationInner = glm::vec3(0);
glm::vec3 mercurScale = glm::vec3(.5f);

glm::vec3 earthOffset = glm::vec3(5, 0, 0);
glm::vec3 earthRotation = glm::vec3(0);
glm::vec3 earthRotationInner = glm::vec3(0);
glm::vec3 earthScale = glm::vec3(.5f);

glm::vec3 moonOffset = glm::vec3(2, 0, 0);
glm::vec3 moonRotation = glm::vec3(0);
glm::vec3 moonRotationInner = glm::vec3(0);
glm::vec3 moonScale = glm::vec3(.2f);

void UniverseScene::createModels()
{
	modelManager.registerModel("cubeVertexData", ModelLoader::convertToVector(cubeVertexData));
	modelManager.registerModel("sphere", ModelLoader::convertToVector(sphere));

	//sun
	models.push_back(GameObjectBuilder<OffsetRotator>()
		.addTransform(new ScaleTransform(&globalscale))
		.addChild(ModelBuilder()
			.name("sun")
			.setVertexData(modelManager.getModel("sphere"))
			.addTransform(new ScaleTransform(&sunScale))
			.addTransform(new RotationTransform(&sunRotationInner))
			.setShader(shaderPrograms[std::string("lightShader")])
			.setBasicTransforms()
			.finish())
		.addChild(GameObjectBuilder<OffsetRotator>()
			.name("fromCenterRotation")
			.addTransform(new ScaleTransform(&mercurScale))
			.addTransform(new TranslationTransform(&mercurOffset))
			.addTransform(new RotationTransform(&mercurRotation))
			.addChild(ModelBuilder()
				.name("mecrury")
				.setVertexData(modelManager.getModel("cubeVertexData"), POS4_COL4)
				.addTransform(new RotationTransform(&mercurRotationInner))
				.setShader(shaderPrograms["secondShader"])
				.finish())
			.finish())
		.addChild(GameObjectBuilder<OffsetRotator>()
			.name("fromCenterRotation")
			.addTransform(new ScaleTransform(&earthScale))
			.addTransform(new TranslationTransform(&earthOffset))
			.addTransform(new RotationTransform(&earthRotation))
			.addChild(ModelBuilder()
				.name("earthModel")
				.setVertexData(modelManager.getModel("cubeVertexData"), POS4_COL4)
				.addTransform(new RotationTransform(&earthRotationInner))
				.setShader(shaderPrograms["secondShader"])
				.finish())
			.addChild(ModelBuilder()
				.name("moonModel")
				.setVertexData(modelManager.getModel("sphere"))
				.setShader(shaderPrograms["lightShader"])
				.addTransform(new ScaleTransform(&moonScale))
				.addTransform(new RotationTransform(&moonRotationInner))
				.addTransform(new TranslationTransform(&moonOffset))
				.addTransform(new RotationTransform(&moonRotation))
				.finish())
			.finish())
		.finish()
	);

	models[0]->getPosition()->z = 4;;
}

void UniverseScene::tick(float deltaTime)
{
	deltaTime = deltaTime * .5f;
	Scene::tick(deltaTime);

	sunRotationInner.x += deltaTime * 1.5f;
	sunRotationInner.z += deltaTime * 1.5f;

	mercurRotation.z += deltaTime;
	mercurRotationInner.x += deltaTime * 1.5f;
	mercurRotationInner.z += deltaTime * 1.5f;

	earthRotation.z += deltaTime * -.5f;
	earthRotationInner.x += deltaTime * 1.5f;
	earthRotationInner.y += deltaTime * 15;
	earthRotationInner.z += deltaTime * 1.5f;

	moonRotation.z += deltaTime * 2;
	moonRotationInner.x += deltaTime * 1.5f;
	moonRotationInner.y += deltaTime * 1.5f;
	moonRotationInner.z += deltaTime * 1.5f;
}

void UniverseScene::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
