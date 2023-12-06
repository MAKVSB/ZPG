#include "MoveScene.h"
#include <Scene/Objects/Skybox.h>
#include <random>
#include "Utils.h"

MoveScene::MoveScene(GLFWwindow* window) : Scene(window) {
	float circleRadius = 10;
	A = glm::mat4(
		glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0)
	);
	B = glm::mat4x3(
		glm::vec3(0, 0, 0),			// P0
		glm::vec3(0, 0.665f * circleRadius, 0),    // P1
		glm::vec3(1 * circleRadius, 0.665f * circleRadius, 0),    // P2
		glm::vec3(1 * circleRadius, 0, 0)			// P3
	);
	C = std::vector<glm::vec3>{
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0.665f * circleRadius, 0),
		glm::vec3(1 * circleRadius, 0.665f * circleRadius, 0),
		/**/glm::vec3(1 * circleRadius, 0, 0),
		glm::vec3(1 * circleRadius, -0.665f * circleRadius, 0),
		glm::vec3(0, -0.665f * circleRadius, 0),
		/**/glm::vec3(0, 0, 0),
		glm::vec3(0, 0.665f * circleRadius, 0),
		glm::vec3(-1 * circleRadius, 0.665f * circleRadius, 0),
		/**/glm::vec3(-1 * circleRadius, 0, 0),
		glm::vec3(-1 * circleRadius, -0.665f * circleRadius, 0),
		glm::vec3(0, -0.665f * circleRadius, 0),
		/**/glm::vec3(0, 0, 0),
	};
	D = std::vector<glm::vec3>{
		glm::vec3(0, 0, 0),
		glm::vec3(0, 0.665f * circleRadius, 0),
		glm::vec3(1 * circleRadius, 0.665f * circleRadius, 0),
		/**/glm::vec3(1 * circleRadius, 0, 0),
		glm::vec3(1 * circleRadius, 0.665f * circleRadius, 0),
		glm::vec3(2 * circleRadius, 0.665f * circleRadius, 0),
		/**/glm::vec3(2 * circleRadius, 0, 0),
		glm::vec3(2 * circleRadius, 0.665f * circleRadius, 0),
		glm::vec3(3 * circleRadius, 0.665f * circleRadius, 0),
		/**/glm::vec3(3 * circleRadius, 0, 0),
		glm::vec3(3 * circleRadius, 0.665f * circleRadius, 0),
		glm::vec3(4 * circleRadius, 0.665f * circleRadius, 0),
		/**/glm::vec3(4 * circleRadius, 0, 0),
	};
	createShaders();
	createModels();
}

MoveScene::~MoveScene()
{

}

void MoveScene::createShaders()
{
	shaderPrograms["lightShader"] = ShaderBuilder()
		.name("lightShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/lightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/lightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["lightShader"]);

	shaderPrograms["texturedLightShader"] = ShaderBuilder()
		.name("texturedLightShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/texturedLightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/texturedLightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["texturedLightShader"]);

	shaderPrograms["skyboxShader"] = ShaderBuilder()
		.name("skyboxShader3")
		.addShader(GL_VERTEX_SHADER, "Shaders/skybox/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/skybox/fragment.glsl")
		.compileAndCheck()
		->setCamera(camera);
}

void MoveScene::createModels()
{
	meshManager.registerMesh("plain", Mesh(plainTextured, POS3_NOR3_TEX2));
	meshManager.registerMesh("tree", Mesh(tree));

	materialManager["grass"] = Material();
	materialManager["grass"].texture.loadTexture2D("C:/Users/mdani/Downloads/multipletextures/grass.png");
	materialManager["skybox"] = Material();
	materialManager["skybox"].r_a = glm::vec3(.05f);
	materialManager["skybox"].texture.createCubeMap({ "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" }, "C:/Users/mdani/Downloads/cubemap/");


	Light* light = new Light();
	light->setLightType(LightType::AMBIENT);
	light->setPosition(glm::vec3(0));
	light->setLightColor(glm::vec3(0));
	light->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	light->setLightStrength(32);
	models.push_back(light);

	Light* light2 = new Light();
	light2->setLightType(LightType::SPOTLIGHT);
	light2->setPosition(glm::vec3(0, 7, 0));
	light2->setLightColor(glm::vec3(1, 1, 1));
	light2->setLightAttenuation(glm::vec3(0.5, 0.1, 0.05));
	light2->setLightStrength(32);
	light2->setCutoff(10);
	models.push_back(light2);

	Light* light3 = new Light();
	light3->setLightType(LightType::POINT);
	light3->setPosition(glm::vec3(0, 0, 0));
	light3->setRotation(glm::vec3(1, 0, 0));
	light3->setLightColor(glm::vec3(1, 1, 1));
	light3->setLightAttenuation(glm::vec3(2, 0.18f, 3));
	light3->setLightStrength(32.0f);
	models.push_back(light3);

	Skybox* skybox = new Skybox();
	skybox->setShader(shaderPrograms[std::string("skyboxShader")]);
	skybox->setMaterial(&materialManager["skybox"]);
	models.push_back(skybox);

	float terrainSize = 20;
	models.push_back(ModelBuilder()
		.setMesh(meshManager.getMesh("plain"))
		.setShader(shaderPrograms[std::string("texturedLightShader")])
		.setScale(glm::vec3(terrainSize*2, 1, terrainSize*2))
		.setMaterial(&materialManager["grass"])
		.setTextureScale(glm::vec2(terrainSize))
		.setBasicTransforms()
		.setId(1)
		.finish());
	indexUsageMap[1] = true;

	polyLinePoints.push_back(glm::vec3(0, 10, 0));
	polyLinePoints.push_back(glm::vec3(10, 10, 0));
	polyLinePoints.push_back(glm::vec3(10, 0, 0));
	polyLinePoints.push_back(glm::vec3(0, 0, 0));























	ModelLoader ml = ModelLoader(&meshManager, &materialManager, shaderPrograms["texturedLightShader"], POS3_NOR3_TEX2);

	GameObject* loadedModel6 = ml.loadModel("Models/Seahawk/Seahawk.obj");
	loadedModel6->name = "Seahawk";
	loadedModel6->setPosition(glm::vec3(0, 10, 0));
	loadedModel6->setScale(glm::vec3(.1f));
	//loadedModel6->tc->add(new LineTransform(new glm::vec3(30, 0, 0), &moveTime));
	//loadedModel6->tc->add(new PolyLineTransform(&polyLinePoints, &moveTime));
	//loadedModel6->tc->add(new BezierTransform(&A, &B, &moveTime));
	loadedModel6->tc->add(new PolyBezierTransform(&A, &C, &moveTime));


	GameObject* loadedModel7 = ml.loadModel("Models/Seahawk/Seahawk_rotor.obj");
	loadedModel7->name = "Seahawk_rotor";
	loadedModel7->setPosition(glm::vec3(0, 41, 25));
	loadedModel6->addChild(loadedModel7);

	GameObject* loadedModel8 = ml.loadModel("Models/Seahawk/Seahawk_rotor_small.obj");
	loadedModel8->name = "Seahawk_rotor_small";
	loadedModel8->setPosition(glm::vec3(-2.2f, 47, -100));
	loadedModel6->addChild(loadedModel8);

	models.push_back(loadedModel6);
	// oprava materiálù protože moje shadery používají hodnoty jinak než blender oèekává
	#pragma region MyRegion
		glm::vec3 seahawkColor = glm::vec3(0.7f);
		materialManager["Models/Seahawk/Seahawk.obj4"].objectColor = seahawkColor; // barva fuselage
		materialManager["Models/Seahawk/Seahawk.obj7"].objectColor = seahawkColor; // zadní stabilizátor / okna
		materialManager["Models/Seahawk/Seahawk.obj9"].objectColor = seahawkColor; // bílé zbranì a fuselage
		materialManager["Models/Seahawk/Seahawk.obj21"].objectColor = seahawkColor; // vrtule
		materialManager["Models/Seahawk/Seahawk.obj12"].objectColor = glm::vec3(1, 0.1f, 0.1f); // èervenné svìtla
		materialManager["Models/Seahawk/Seahawk.obj20"].objectColor = glm::vec3(0.05f, 0.05f, 0.05f); // pleumatiky
		materialManager["Models/Seahawk/Seahawk.obj17"].objectColor = glm::vec3(0.21f, 0.08f, 0); // sedaèky
		materialManager["Models/Seahawk/Seahawk.obj19"].objectColor = glm::vec3(0.21f, 0.08f, 0); // zadní sedaèky
		materialManager["Models/Seahawk/Seahawk.obj10"].objectColor = glm::vec3(0.2f, 0.2f, 0.2f); // nalešnìný kov (tyèky na bocích, kola, tyèe sedaèek)
		materialManager["Models/Seahawk/Seahawk.obj15"].objectColor = glm::vec3(0.01f, 0.01f, 0.01f); // èerná -> vnitøek výfuku
		materialManager["Models/Seahawk/Seahawk.obj6"].objectColor = glm::vec3(1, 1, 1); // svìtla ve pøedu
		materialManager["Models/Seahawk/Seahawk.obj2"].objectColor = glm::vec3(0.01, 0.01, 0.01); // okna
		materialManager["Models/Seahawk/Seahawk.obj2"].r_s = glm::vec3(100, 100, 100); // okna
		materialManager["Models/Seahawk/Seahawk.obj2"].r_d = glm::vec3(10, 10, 10); // okna
		materialManager["Models/Seahawk/Seahawk.obj18"].objectColor = glm::vec3(0.21f, 0.08f, 0); // opìrátka sedaèek
		materialManager["Models/Seahawk/Seahawk.obj8"].objectColor = glm::vec3(0.2f, 0.2f, 0.2f); // tmavì èerné výfuky a nusná soustava vrtule
		materialManager["Models/Seahawk/Seahawk_rotor.obj0"].objectColor = seahawkColor; // vrtule
		materialManager["Models/Seahawk/Seahawk_rotor.obj1"].objectColor = seahawkColor; // vrtule
		materialManager["Models/Seahawk/Seahawk_rotor.obj2"].objectColor = seahawkColor; // vrtule
		materialManager["Models/Seahawk/Seahawk_rotor.obj3"].objectColor = seahawkColor; // vrtule
		materialManager["Models/Seahawk/Seahawk_rotor.obj4"].objectColor = seahawkColor; // vrtule
		materialManager["Models/Seahawk/Seahawk_rotor_small.obj2"].objectColor = seahawkColor; // vrtule
		materialManager["Models/Seahawk/Seahawk_rotor_small.obj1"].objectColor = glm::vec3(0.2f, 0.2f, 0.2f); // tmavì èerné výfuky a nusná soustava vrtule
	#pragma endregion

	Light* light10 = new Light();
	light10->setLightType(LightType::POINT);
	light10->setPosition(glm::vec3(0, 20, 0));
	light10->setLightAttenuation(glm::vec3(0));
	light10->setLightStrength(32.0f);
	models.push_back(light10);
	//light10->enabled = false;


	camera->setPosition(glm::vec3(0, 1.4, 0));
	lightManager.updateLightReferences(models);
}

void MoveScene::tick(float deltaTime)
{
	Scene::tick(deltaTime);
	((Light*)models[2])->setRotation(*camera->getRotation());
	((Light*)models[3])->setPosition(*camera->getPosition());
	models[6]->childs[39]->updateRotation(glm::vec3(0, deltaTime*40, 0));
	models[6]->childs[40]->updateRotation(glm::vec3(deltaTime *40, 0, 0));

	float moveTimeBefore = moveTime;

	//if (moveTime >= 1.0f || moveTime <= 0.0f) moveDelta *= -1; //line
	//if (moveTime >= polyLinePoints.size() || moveTime <= 0.0f) moveDelta *= -1; //polyline
	//if (moveTime >= 1.0f || moveTime <= 0.0f) moveDelta *= -1; //bezier
	if (moveTime >= 4.0f || moveTime <= 0.0f) moveDelta *= -1; //polybezier
	moveTime += moveDelta * deltaTime;
	moveTime = glm::clamp(moveTime, 0.0f, 4.0f);

	//LineTransformStatic::transform(models[6], glm::vec3(30, 0, 0), moveTimeBefore, moveTime);
	//PolyLineTransformStatic::transform(models[6], polyLinePoints, moveTimeBefore, moveTime);
	//BezierTransformStatic::transform(models[6], A, B, moveTimeBefore, moveTime);
	//PolyBezierTransformStatic::transform(models[6], A, C, moveTimeBefore, moveTime, 0.5);
}

void MoveScene::drawDebugElement()
{
	Scene::drawDebugElement();
	for (auto& mat : materialManager) {
		ImGui::Begin("Material Debugger");
		if (ImGui::TreeNode(mat.first.c_str())) {
			ImGui::DragFloat3("Ambient", glm::value_ptr(mat.second.r_a), 0.1f, 0, 1);
			ImGui::DragFloat3("Diffuze", glm::value_ptr(mat.second.r_d), 0.1f, 0, 1);
			ImGui::DragFloat3("Specular", glm::value_ptr(mat.second.r_s), 0.1f, 0, 1);
			ImGui::DragFloat3("Color", glm::value_ptr(mat.second.objectColor), 0.1f, 0, 1);
			ImGui::TreePop();
		}

		// End the window
		ImGui::End();
	}
}

void MoveScene::listen(MessageType messageType, void* object)
{
	if (messageType == MessageType::MouseButtonPressed) {
		int x = (int)((CallbackManager::CBButtonData*)object)->mousePos.x;
		int y = (int)((CallbackManager::CBButtonData*)object)->mousePos.y;

		// size of window
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		GLbyte color[4];
		GLfloat depth;
		GLuint index; // identifikace tìlesa
		int newy = height - y;
		glReadPixels(x, newy, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, color);
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		glm::vec3 pos = glm::unProject(glm::vec3(x, newy, depth), camera->getViewMatrix(), camera->getProjectionMartix(), glm::vec4(0, 0, width, height));

		if (index == 0) {
			return;
		}

		if (index == 1) {
		}
	}
}