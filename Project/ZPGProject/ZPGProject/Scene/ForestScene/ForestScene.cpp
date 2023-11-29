#include "ForestScene.h"

ForestScene::ForestScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void ForestScene::createShaders()
{
	shaderPrograms["lightShader"] = ShaderBuilder()
		.name("lightShader1")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	shaderPrograms["texturedLightShader"] = ShaderBuilder()
		.name("lightShader2")
		.addShader(GL_VERTEX_SHADER, "Shaders/texturedLightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/texturedLightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["lightShader"]);
	shaderPrograms["skyboxShader"] = ShaderBuilder()
		.name("skyboxShader3")
		.addShader(GL_VERTEX_SHADER, "Shaders/skybox/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/skybox/fragment.glsl")
		.compileAndCheck()
		->setCamera(camera);
}

Light* alight;
Light* alight2;

void ForestScene::createModels()
{
	meshManager.registerMesh("tree", Mesh(tree));
	meshManager.registerMesh("bushes", Mesh(bushes));
	meshManager.registerMesh("gift", Mesh(gift));
	meshManager.registerMesh("plain", Mesh(plainTextured, POS3_NOR3_TEX2));

	float distance = 0.7f;

	alight = new Light();
	alight->setLightType(LightType::SPOTLIGHT);
	alight->setPosition(glm::vec3(0, 7, 0));
	alight->setLightColor(glm::vec3(1, 1, 1));
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
	light4->setLightColor(glm::vec3(0.3, 0.3, 0.3));
	models.push_back(light4);

	materialManager["default"] = Material();
	materialManager["default"].r_a = glm::vec4(1);
	materialManager["default"].r_d = glm::vec4(1);
	materialManager["default"].r_s = glm::vec4(2);
	materialManager["default"].objectColor = glm::vec3(0.2f, 1, 0.2f);

	materialManager["gift"] = Material();
	materialManager["gift"].r_s = glm::vec4(6);
	materialManager["gift"].objectColor = glm::vec3(0.9f, 0.2f, 0.2f);

	materialManager["skybox"] = Material();
	materialManager["skybox"].r_a = glm::vec3(.1f);
	materialManager["skybox"].texture.createCubeMap({ "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" }, "C:/Users/mdani/Downloads/cubemap/");

	materialManager["grass"] = Material();
	materialManager["grass"].texture.loadTexture2D("C:/Users/mdani/Downloads/multipletextures/grass.png");

	// skybox
	Skybox* skybox = new Skybox();
	skybox->setShader(shaderPrograms[std::string("skyboxShader")]);
	skybox->setMaterial(&materialManager["skybox"]);
	models.push_back(skybox);

	camera->setPosition(glm::vec3(0, 1, 2));
	camera->invalidate();

	int terrainSize = 10;

	for (int i = -terrainSize; i < terrainSize;i++) {
		for (int j = -terrainSize; j < terrainSize;j++) {
			models.push_back(ModelBuilder()
				.setMesh(meshManager.getMesh("plain"))
				.setShader(shaderPrograms[std::string("texturedLightShader")])
				.setPosition(glm::vec3(i * 2, 0, j * 2))
				.setMaterial(&materialManager["grass"])
				.setBasicTransforms()
				.finish());
		}
	}

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution((2 * -terrainSize)-(1-0.1f), (2 * terrainSize)-(1+0.2f));

	// Generate random trees
	for (int i = 0; i < 100; i++) {
		models.push_back(ModelBuilder()
			.setMesh(meshManager.getMesh("tree"))
			.setShader(shaderPrograms[std::string("lightShader")])
			.setPosition(glm::vec3(distribution(gen), 0, distribution(gen)))
			.setRotation(glm::vec3(0, distribution(gen), 0))
			.setScale(glm::vec3(.8f))
			.setMaterial(&materialManager["default"])
			.setBasicTransforms()
			.finish());
	}

	// Generate random bushes
	for (int i = 0; i < 1000; i++) {
		models.push_back(ModelBuilder()
			.setMesh(meshManager.getMesh("bushes"))
			.setShader(shaderPrograms[std::string("lightShader")])
			.setPosition(glm::vec3(distribution(gen), 0, distribution(gen)))
			.setRotation(glm::vec3(0, distribution(gen), 0))
			.setScale(glm::vec3(.8f))
			.setMaterial(&materialManager["default"])
			.setBasicTransforms()
			.finish());
	}

	// Generate random gifts
	for (int i = 0; i < 100; i++) {
		models.push_back(ModelBuilder()
			.setMesh(meshManager.getMesh("gift"))
			.setShader(shaderPrograms[std::string("lightShader")])
			.setPosition(glm::vec3(distribution(gen), 0, distribution(gen)))
			.setRotation(glm::vec3(0, distribution(gen), 0))
			.setMaterial(&materialManager["gift"])
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
	Scene::draw();
}
