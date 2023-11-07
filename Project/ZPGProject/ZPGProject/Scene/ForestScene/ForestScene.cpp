#include "ForestScene.h"

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
}

Light* alight;
Light* alight2;

void ForestScene::createModels()
{
	meshManager.registerMesh("tree", Mesh(tree));
	meshManager.registerMesh("bushes", Mesh(bushes));
	meshManager.registerMesh("sphere", Mesh(sphere));
	meshManager.registerMesh("plain", Mesh(plain));

	float distance = 0.7f;

	alight = new Light();
	alight->setLightType(LightType::SPOTLIGHT);
	alight->setPosition(glm::vec3(0, 7, 0));
	alight->setLightColor(glm::vec3(1, 0, 0));
	alight->setLightAttenuation(glm::vec3(0.5, 0.1, 0.1));
	alight->setLightStrength(32);
	alight->setCutoff(10);
	models.push_back(alight);

	alight2 = new Light();
	alight2->setLightType(LightType::POINT);
	alight2->setPosition(glm::vec3(0, 0, 0));
	alight2->setLightColor(glm::vec3(0.4, 0.4, 0.4));
	models.push_back(alight2);

	Light* light4 = new Light();
	light4->setLightType(LightType::AMBIENT);
	light4->setPosition(glm::vec3(0, 0, 0));
	light4->setLightColor(glm::vec3(0.2, 0.2, 0.2));
	models.push_back(light4);

	Material m;
	m.r_a = glm::vec4(1);
	m.r_d = glm::vec4(1);
	m.r_s = glm::vec4(2);
	m.objectColor = glm::vec3(0.2f, 1, 0.2f);

	camera->setPosition(glm::vec3(0, 1, 2));

	int terrainSize = 10;

	for (int i = -terrainSize; i < terrainSize;i++) {
		for (int j = -terrainSize; j < terrainSize;j++) {
			models.push_back(ModelBuilder()
				.setMesh(meshManager.getMesh("plain"))
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
			.setMesh(meshManager.getMesh("tree"))
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
			.setMesh(meshManager.getMesh("bushes"))
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
			.setMesh(meshManager.getMesh("sphere"))
			.setShader(shaderPrograms[std::string("lightShader")])
			.setPosition(glm::vec3(distribution(gen)/ terrainSize, 0.5f, distribution(gen)/ terrainSize))
			.setScale(glm::vec3(.5f))
			.setMaterial(m)
			.setBasicTransforms()
			.finish());
	}

	lightManager.updateLightReferences(models);
}

void ForestScene::tick(float deltaTime)
{
	Scene::tick(deltaTime);
	alight->setPosition(*camera->getPosition());
	alight2->setPosition(*camera->getPosition());
	alight->setLightDirection(*camera->getRotation());
}

void ForestScene::draw()
{
	// clear color and depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	Scene::draw();
}
