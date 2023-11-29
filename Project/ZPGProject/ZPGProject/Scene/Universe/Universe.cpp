#include "Universe.h"
#include <Scene/Objects/Skybox.h>

UniverseScene::UniverseScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
}

void UniverseScene::createShaders()
{
	shaderPrograms["lightShader"] = ShaderBuilder()
		.name("lightShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/texturedLightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/texturedLightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["lightShader"]);
	shaderPrograms["secondShader"] = ShaderBuilder()
		.name("secondShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/vertex_shader_positional_color.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/fragment_shader_color_positional.glsl")
		.compileAndCheck()
		->setCamera(camera);
	shaderPrograms["skyboxShader"] = ShaderBuilder()
		.name("skyboxShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/skybox/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/skybox/fragment.glsl")
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

Skybox* skybox;
void UniverseScene::createModels()
{
	meshManager.registerMesh("gift", gift);
	meshManager.registerMesh("sphere", sphere);
	meshManager.registerMesh("plainTextured", Mesh(plainTextured, POS3_NOR3_TEX2));
	meshManager.registerMesh("plain", Mesh(plain, POS3_NOR3_TEX2));

	Light* light = new Light();
	light->setLightType(LightType::POINT);
	light->setPosition(glm::vec3(0, 1, 0));
	light->setLightColor(glm::vec3(1, 1, 1));
	light->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	light->setLightStrength(32.0f);
	models.push_back(light);

	materialManager["grass"] = Material();
	materialManager["grass"].texture.loadTexture2D("C:/Users/mdani/Downloads/multipletextures/grass.png");
	materialManager["skybox"] = Material();
	materialManager["skybox"].r_a = glm::vec3(.1f);
	materialManager["skybox"].texture.createCubeMap({ "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" }, "C:/Users/mdani/Downloads/cubemap/");
	
	// skybox
	skybox = new Skybox();
	skybox->setShader(shaderPrograms[std::string("skyboxShader")]);
	skybox->setMaterial(&materialManager["skybox"]);
	models.push_back(skybox);

	models.push_back(ModelBuilder()
		.setMesh(meshManager.getMesh("plainTextured"))
		.setShader(shaderPrograms["lightShader"])
		.setMaterial(&materialManager["grass"])
		.setBasicTransforms()
		.finish());

	models.push_back(ModelBuilder()
		.setMesh(meshManager.getMesh("plainTextured"))
		.setShader(shaderPrograms["lightShader"])
		.setPosition(glm::vec3(2,0,0))
		.setMaterial(&materialManager["grass"])
		.setBasicTransforms()
		.finish());

	//sun
	/*models.push_back(GameObjectBuilder<OffsetRotator>()
		.addTransform(new ScaleTransform(&globalscale))
		.addChild(ModelBuilder()
			.name("sun")
			.setMesh(meshManager.getMesh("plainTextured"))
			.setMaterial(mat)
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
				.setMesh(meshManager.getMesh("gift"))
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
				.setMesh(meshManager.getMesh("gift"))
				.addTransform(new RotationTransform(&earthRotationInner))
				.setShader(shaderPrograms["secondShader"])
				.finish())
			.addChild(ModelBuilder()
				.name("moonModel")
				.setMesh(meshManager.getMesh("sphere"))
				.setShader(shaderPrograms["lightShader"])
				.addTransform(new ScaleTransform(&moonScale))
				.addTransform(new RotationTransform(&moonRotationInner))
				.addTransform(new TranslationTransform(&moonOffset))
				.addTransform(new RotationTransform(&moonRotation))
				.finish())
			.finish())
		.finish()
	);*/

	models[0]->getPosition()->z = 4;
	camera->invalidate();
	lightManager.updateLightReferences(models);
}

void UniverseScene::tick(float deltaTime)
{
	//deltaTime = deltaTime * .5f;
	Scene::tick(deltaTime);

	//sunRotationInner.x += deltaTime * 1.5f;
	//sunRotationInner.z += deltaTime * 1.5f;

	//mercurRotation.z += deltaTime;
	//mercurRotationInner.x += deltaTime * 1.5f;
	//mercurRotationInner.z += deltaTime * 1.5f;

	//earthRotation.z += deltaTime * -.5f;
	//earthRotationInner.x += deltaTime * 1.5f;
	//earthRotationInner.y += deltaTime * 15;
	//earthRotationInner.z += deltaTime * 1.5f;

	//moonRotation.z += deltaTime * 2;
	//moonRotationInner.x += deltaTime * 1.5f;
	//moonRotationInner.y += deltaTime * 1.5f;
	//moonRotationInner.z += deltaTime * 1.5f;
}

void UniverseScene::draw()
{
	Scene::draw();
}
