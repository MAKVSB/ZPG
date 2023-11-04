#include "ForestScene.h"

#include "CallbackManager.h"

ForestScene::ForestScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void ForestScene::createShaders()
{
	shaderPrograms["lightShader"] = ShaderBuilder()
		.name("lightShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["lightShader"]);

	//shaderPrograms["secondShader"] = ShaderBuilder()
	//	.name("secondShader")
	//	.addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_positional_color.glsl")
	//	.addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_positional.glsl")
	//	.compileAndCheck()
	//	->setCamera(camera);
}

Light* light;
Light* light2;

void ForestScene::createModels()
{
	modelManager.registerModel("tree", ModelLoader::convertToVector(tree));
	modelManager.registerModel("sphere", ModelLoader::convertToVector(sphere));
	modelManager.registerModel("plain", ModelLoader::convertToVector(plain));
	modelManager.registerModel("bushes", ModelLoader::convertToVector(bushes));
	modelManager.registerModel("suziSmooth", ModelLoader::convertToVector(suziSmooth));



	float distance = 0.7f;

	light = new Light();
	light->setLightType(LightType::SPOTLIGHT);
	light->setPosition(glm::vec3(0, 7, 0));
	light->setLightColor(glm::vec3(1, 1, 1));
	light->setLightAttenuation(glm::vec3(0.5, 0.1, 0.1));
	light->setLightStrength(32);
	light->setCutoff(10);
	models.push_back(light);

	light2 = new Light();
	light2->setLightType(LightType::POINT);
	light2->setPosition(glm::vec3(0, 0, 0));
	light2->setLightColor(glm::vec3(0.4, 0.4, 0.4));
	models.push_back(light2);

	Light* light4 = new Light();
	light4->setLightType(LightType::AMBIENT);
	light4->setPosition(glm::vec3(0, 0, 0));
	light4->setLightColor(glm::vec3(0.2, 0.2, 0.2));
	models.push_back(light4);

	Material m;
	m.r_a = glm::vec4(1);
	m.r_d = glm::vec4(1);
	m.r_s = glm::vec4(2);
	m.objectColor = glm::vec3(0, 1, 0);

	camera->setPosition(glm::vec3(0, 1, 2));

	int terrainSize = 10;

	for (int i = -terrainSize; i < terrainSize;i++) {
		for (int j = -terrainSize; j < terrainSize;j++) {
			models.push_back(ModelBuilder()
				.setVertexData(modelManager.getModel("plain"))
				.setShader(shaderPrograms[std::string("lightShader")])
				.setPosition(glm::vec3(i * 2, 0, j * 2))
				.setMaterial(m)
				.setBasicTransforms()
				.finish());
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution((2 * -terrainSize)-(1-0.1f), (2 * terrainSize)-(1+0.2f));

	// Generate random trees
	for (int i = 0; i < 300; i++) {
		models.push_back(ModelBuilder()
			.setVertexData(modelManager.getModel("tree"))
			.setShader(shaderPrograms[std::string("lightShader")])
			.setPosition(glm::vec3(distribution(gen), 0, distribution(gen)))
			.setScale(glm::vec3(.8f))
			.setMaterial(m)
			.setBasicTransforms()
			.finish());
	}

	// Generate random bushes
	for (int i = 0; i < 1000; i++) {
		models.push_back(ModelBuilder()
			.setVertexData(modelManager.getModel("bushes"))
			.setShader(shaderPrograms[std::string("lightShader")])
			.setPosition(glm::vec3(distribution(gen), 0, distribution(gen)))
			.setScale(glm::vec3(.8f))
			.setMaterial(m)
			.setBasicTransforms()
			.finish());
	}

	// Generate random spheres
	for (int i = 0; i < 3; i++) {
		models.push_back(ModelBuilder()
			.setVertexData(modelManager.getModel("sphere"))
			.setShader(shaderPrograms[std::string("lightShader")])
			.setPosition(glm::vec3(distribution(gen)/ terrainSize, 0.5f, distribution(gen)/ terrainSize))
			.setScale(glm::vec3(.5f))
			.setMaterial(m)
			.setBasicTransforms()
			.finish());
	}

	// Generate random suzis
	//for (int i = 0; i < 3; i++) {
	//	models.push_back(ModelBuilder()
	//		.setVertexData(modelManager.getModel("suziSmooth"))
	//		.setShader(shaderPrograms[std::string("secondShader")])
	//		.setPosition(glm::vec3(distribution(gen)/ terrainSize, 0.5f, distribution(gen)/ terrainSize))
	//		.setScale(glm::vec3(.5f))
	//		.setMaterial(m)
	//		.setBasicTransforms()
	//		.finish());
	//}

	lightManager.updateLightReferences(models);
}

void ForestScene::tick(float deltaTime)
{
	light->setPosition(*camera->getPosition());
	light2->setPosition(*camera->getPosition());
	light->setLightDirection(*camera->getRotation());

	Scene::tick(deltaTime);
}

void ForestScene::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
