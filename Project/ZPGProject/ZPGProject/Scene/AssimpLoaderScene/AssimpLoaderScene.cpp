#include "AssimpLoaderScene.h"
#include <Scene/Objects/Skybox.h>
#include <random>
#include "Utils.h"

AssimpLoaderScene::AssimpLoaderScene(GLFWwindow* window) : Scene(window) {
	createShaders();
	createModels();
	CallbackManager::getInstance()->add(this);
}

AssimpLoaderScene::~AssimpLoaderScene()
{
	CallbackManager::getInstance()->remove(this);
}

void AssimpLoaderScene::createShaders()
{
	shaderPrograms["phongShader"] = ShaderBuilder()
		.name("phongShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/texturedLightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/texturedLightShader/phong.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["phongShader"]);

	shaderPrograms["blinnShader"] = ShaderBuilder()
		.name("blinnShader")
		.addShader(GL_VERTEX_SHADER, "Shaders/texturedLightShader/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/texturedLightShader/blinn.glsl")
		.compileAndCheck()
		->setCamera(camera);
	lightManager.attachShader(shaderPrograms["blinnShader"]);

	shaderPrograms["skyboxShader"] = ShaderBuilder()
		.name("skyboxShader3")
		.addShader(GL_VERTEX_SHADER, "Shaders/skybox/vertex.glsl")
		.addShader(GL_FRAGMENT_SHADER, "Shaders/skybox/fragment.glsl")
		.compileAndCheck()
		->setCamera(camera);
}

void AssimpLoaderScene::createModels()
{
	meshManager.registerMesh("plain", Mesh(plainTextured, POS3_NOR3_TEX2));
	meshManager.registerMesh("gift", Mesh(gift));
	meshManager.registerMesh("tree", Mesh(tree));

	materialManager["grass"] = Material();
	materialManager["grass"].texture.loadTexture2D("C:/Users/mdani/Downloads/multipletextures/grass.png");
	materialManager["skybox"] = Material();
	materialManager["skybox"].r_a = glm::vec3(.05f);
	materialManager["skybox"].texture.createCubeMap({ "posx.jpg", "negx.jpg", "posy.jpg", "negy.jpg", "posz.jpg", "negz.jpg" }, "C:/Users/mdani/Downloads/cubemap/");
	materialManager["gift0"] = Material();
	materialManager["gift0"].r_s = glm::vec4(6);
	materialManager["gift0"].objectColor = glm::vec3(0.9f, 0.9f, 0.2f);
	materialManager["gift1"] = Material();
	materialManager["gift1"].r_s = glm::vec4(6);
	materialManager["gift1"].objectColor = glm::vec3(0.9f, 0.2f, 0.2f);
	materialManager["gift2"] = Material();
	materialManager["gift2"].r_s = glm::vec4(6);
	materialManager["gift2"].objectColor = glm::vec3(0.2f, 0.9f, 0.2f);
	materialManager["gift3"] = Material();
	materialManager["gift3"].r_s = glm::vec4(6);
	materialManager["gift3"].objectColor = glm::vec3(0.2f, 0.2f, 0.9f);
	materialManager["gift4"] = Material();
	materialManager["gift4"].r_s = glm::vec4(6);
	materialManager["gift4"].objectColor = glm::vec3(0.2f, 0.9f, 0.9f);
	materialManager["snowyTree"] = Material();
	materialManager["snowyTree"].r_s = glm::vec4(6);
	materialManager["snowyTree"].objectColor = glm::vec3(1, 1, 1);
	materialManager["tree"] = Material();
	materialManager["tree"].r_a = glm::vec4(1);
	materialManager["tree"].r_d = glm::vec4(1);
	materialManager["tree"].r_s = glm::vec4(2);
	materialManager["tree"].objectColor = glm::vec3(0.2f, 1, 0.2f);


	Light* light = new Light();
	light->setLightType(LightType::AMBIENT);
	light->setLightColor(glm::vec3(0));
	light->setLightAttenuation(glm::vec3(1, 0.36f, 0.256f));
	models.push_back(light);

	Light* light2 = new Light();
	light2->setLightType(LightType::SPOTLIGHT);
	light2->setPosition(glm::vec3(0, 7, 0));
	light2->setLightColor(glm::vec3(1, 1, 1));
	light2->setLightAttenuation(glm::vec3(0.5, 0.1, 0.05));
	light2->setCutoff(10);
	models.push_back(light2);

	Light* light3 = new Light();
	light3->setLightType(LightType::POINT);
	light3->setPosition(glm::vec3(0, 0, 0));
	light3->setRotation(glm::vec3(1, 0, 0));
	light3->setLightColor(glm::vec3(1, 1, 1));
	light3->setLightAttenuation(glm::vec3(2, 0.18f, 3));
	models.push_back(light3);

	Light* light4 = new Light();
	light4->setLightType(LightType::POINT);
	light4->setPosition(glm::vec3(0, 2.415f, -25.337f));
	light4->setRotation(glm::vec3(1, 0, 0));
	light4->setLightColor(glm::vec3(1, 1, 1));
	light4->setLightAttenuation(glm::vec3(0, 0.6f, 0.2f));
	models.push_back(light4);
	flickeringLights.push_back(FlickerLight { light4, 0, .5f});

	Skybox* skybox = new Skybox();
	skybox->setShader(shaderPrograms[std::string("skyboxShader")]);
	skybox->setMaterial(&materialManager["skybox"]);
	models.push_back(skybox);

	float terrainSize = 20;
	models.push_back(ModelBuilder()
		.setMesh(meshManager.getMesh("plain"))
		.setShader(shaderPrograms[std::string("phongShader")])
		.setScale(glm::vec3(terrainSize*100, 1, terrainSize*100))
		.setMaterial(&materialManager["grass"])
		.setTextureScale(glm::vec2(terrainSize*100))
		.setBasicTransforms()
		.setId(1)
		.finish());
	indexUsageMap[1] = true;


	ModelLoader ml = ModelLoader(&meshManager, &materialManager, shaderPrograms["phongShader"], POS3_NOR3_TEX2);

	GameObject* loadedModel2 = ml.loadModel("Models/House/house.obj");
	loadedModel2->setPosition(glm::vec3(0, 0, -15));
	models.push_back(loadedModel2);

	GameObject* loadedModel3 = ml.loadModel("Models/Zombie/zombie.obj");
	loadedModel3->setPosition(glm::vec3(0, 0.13f, -5.4f));
	models.push_back(loadedModel3);

	GameObject* loadedModel4 = ml.loadModel("Models/Cat/cat.obj");
	loadedModel4->setScale(glm::vec3(0.02f));
	loadedModel4->setPosition(glm::vec3(-1.1f, 0.07f, -5.05f));
	loadedModel4->setRotation(glm::vec3(-1.5f, 0, 0.2));
	models.push_back(loadedModel4);

	GameObject* loadedModel5 = ml.loadModel("Models/Cottage/Cottage.obj");
	loadedModel5->name = "Cottage";
	loadedModel5->setPosition(glm::vec3(0, 0, 20));
	models.push_back(loadedModel5);

	GameObject* loadedModel6 = ml.loadModel("Models/Seahawk/Seahawk.obj");
	loadedModel6->name = "Seahawk";
	loadedModel6->tc->add(new PolyLineTransform(&seaHawkPoints, &moveTimeLines));
	loadedModel6->tc->add(new PolyBezierTransform(&coefs, &seaHawkPoints, &moveTimeBezier));
	loadedModel6->setPosition(glm::vec3(0, 10, 0));
	loadedModel6->setScale(glm::vec3(.1f));

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

	seaHawkPoints.push_back(glm::vec3(22, 0, 4));

	Light* light5 = new Light();
	light5->setLightType(LightType::SPOTLIGHT);
	light5->setPosition(glm::vec3(0, 0, 0));
	light5->setRotation(glm::vec3(0, -1, 0));
	light5->setLightColor(glm::vec3(1, 1, 1));
	light5->setLightAttenuation(glm::vec3(0, 0, 0.01f));
	loadedModel6->addChild(light5);

	Light* light6 = new Light();
	light6->setLightType(LightType::POINT);
	light6->setPosition(glm::vec3(0, 0, 0));
	light6->setRotation(glm::vec3(0, -1, 0));
	light6->setLightColor(glm::vec3(1, 1, 1));
	light6->setLightAttenuation(glm::vec3(0, 0, 0.01f));
	loadedModel6->addChild(light6);

	Light* light7 = new Light();
	light7->setLightType(LightType::SPOTLIGHT);
	light7->setPosition(glm::vec3(-0.8f, 6.487f, -28.8f));
	light7->setRotation(glm::vec3(0, 1, 0));
	light7->setLightColor(glm::vec3(1, 0, 0));
	light7->setLightAttenuation(glm::vec3(0, 0, 1.7f));
	light7->setCutoff(140);
	loadedModel6->addChild(light7);
	flickeringLights.push_back(FlickerLight{ light7, 0, .5f });

	GameObject* winterGroup = GameObjectBuilder<GameObject>()
		.name("christmas")
		.setPosition(glm::vec3(4.727, 0, -4.018))
		.setRotation(glm::vec3(0, 0, 0))
		.setBasicTransforms()
		.addChild(ModelBuilder()
			.setMesh(meshManager.getMesh("tree"))
			.setShader(shaderPrograms[std::string("phongShader")])
			.setPosition(glm::vec3(0, 0, 0))
			.setRotation(glm::vec3(0, -30.380, 0))
			.setScale(glm::vec3(.8f))
			.setBasicTransforms()
			.setMaterial(&materialManager["snowyTree"])
			.finish())
		.addChild(GameObjectBuilder<GameObject>()
			.setPosition(glm::vec3(-0.498, 0, 0.326))
			.setRotation(glm::vec3(0, 0, 0))
			.setBasicTransforms()
			.addChild(ModelBuilder()
				.name("gift")
				.setMesh(meshManager.getMesh("gift"))
				.setShader(shaderPrograms[std::string("phongShader")])
				.setMaterial(&materialManager["gift0"])
				.setPosition(glm::vec3(0, 0, 0))
				.setRotation(glm::vec3(0, 0, 0))
				.setId(2)
				.setBasicTransforms()
				.finish())
			.addChild(ModelBuilder()
				.name("gift")
				.setMesh(meshManager.getMesh("gift"))
				.setShader(shaderPrograms[std::string("phongShader")])
				.setMaterial(&materialManager["gift1"])
				.setPosition(glm::vec3(0.144, 0, -0.366))
				.setRotation(glm::vec3(0, -0.169, 0))
				.setId(3)
				.setBasicTransforms()
				.finish())
			.addChild(ModelBuilder()
				.name("gift")
				.setMesh(meshManager.getMesh("gift"))
				.setShader(shaderPrograms[std::string("phongShader")])
				.setMaterial(&materialManager["gift2"])
				.setPosition(glm::vec3(0.388, 0, 0))
				.setRotation(glm::vec3(0, -0.378, 0))
				.setId(4)
				.setBasicTransforms()
				.finish())
			.addChild(ModelBuilder()
				.name("gift")
				.setMesh(meshManager.getMesh("gift"))
				.setShader(shaderPrograms[std::string("phongShader")])
				.setMaterial(&materialManager["gift3"])
				.setPosition(glm::vec3(0.266, 0.297, -0.164))
				.setRotation(glm::vec3(0, 0.533, 0))
				.setId(5)
				.setBasicTransforms()
				.finish())
			.finish())
		.finish();
	models.push_back(winterGroup);
	BoundingBox omg1 = ((Model*)winterGroup->childs[0])->mesh->boundingBox;

	for (int i = 0; i < 20; i++) {

		float posX = Utils::floatRand(omg1.max.x, omg1.min.x);
		float posY = Utils::floatRand(omg1.max.y, omg1.min.y);
		float posZ = Utils::floatRand(omg1.max.z, omg1.min.z);

		Light* randlight = new Light();
		randlight->setLightType(LightType::POINT);
		randlight->setPosition(glm::vec3(
			posX / 2 + winterGroup->getPosition()->x + winterGroup->childs[0]->getPosition()->x,
			posY + winterGroup->getPosition()->y + winterGroup->childs[0]->getPosition()->y,
			posZ / 2 + winterGroup->getPosition()->z + winterGroup->childs[0]->getPosition()->z
		));
		randlight->setLightColor(glm::vec3(
			Utils::floatRand(1, 0),
			Utils::floatRand(1, 0),
			Utils::floatRand(1, 0)
		));
		randlight->setLightAttenuation(glm::vec3(0, 0, 10));
		models.push_back(randlight);
		flickeringLights.push_back(FlickerLight{ randlight, 0, .5f });
	}


	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<float> distribution((2 * -terrainSize) - (1 - 0.1f), (2 * terrainSize) - (1 + 0.2f));

	// Generate random trees
	for (int i = 0; i < 250; i++) {
		int freeIndex = getUnusedIndex(2, 254);
		if (freeIndex == -1) {
			continue;
		}

		float posX = distribution(gen);
		float posY = distribution(gen);

		//if is in square of the house
		while (
			(posX > -5 && posX < 6 && posY < 0 && posY > -27) ||
			(posX > -7 && posX < 7 && posY < 28 && posY > 11) ||
			(posX > 15 && posX < 32 && posY < 15 && posY > -2)
		) {
			posX = distribution(gen);
			posY = distribution(gen);
		}

		models.push_back(ModelBuilder()
			.name("tree")
			.setMesh(meshManager.getMesh("tree"))
			.setShader(shaderPrograms[std::string("blinnShader")])
			.setPosition(glm::vec3(posX, 0, posY))
			.setRotation(glm::vec3(0, distribution(gen), 0))
			.setScale(glm::vec3(.8f))
			.setMaterial(&materialManager["tree"])
			.setBasicTransforms()
			.setId(freeIndex)
			.finish());
		indexUsageMap[freeIndex] = true;
	}

	// Generate random gifts
	for (int i = 6; i < 250; i++) {
		float posX = distribution(gen);
		float posY = distribution(gen);

		//if is in square of the house
		while (
			(posX > -5 && posX < 6 && posY < 0 && posY > -27) ||
			(posX > -7 && posX < 7 && posY < 28 && posY > 11)
			) {
			posX = distribution(gen);
			posY = distribution(gen);
		}

		models.push_back(ModelBuilder()
			.name("gift")
			.setMesh(meshManager.getMesh("gift"))
			.setShader(shaderPrograms[std::string("blinnShader")])
			.setPosition(glm::vec3(posX, 0, posY))
			.setRotation(glm::vec3(0, distribution(gen), 0))
			.setMaterial(&materialManager["gift" + std::to_string(i%5)])
			.setBasicTransforms()
			.setId(i)
			.finish());
	}

	Light* light10 = new Light();
	light10->setLightType(LightType::POINT);
	light10->setPosition(glm::vec3(0, 20, 0));
	light10->setLightAttenuation(glm::vec3(0));
	models.push_back(light10);
	light10->enabled = false;

	camera->setPosition(glm::vec3(0, 1.4, 0));
	lightManager.updateLightReferences(models);
}

void AssimpLoaderScene::tick(float deltaTime)
{
	Scene::tick(deltaTime);
	((Light*)models[2])->setPosition(*camera->getPosition());
	((Light*)models[2])->setRotation(*camera->getRotation());
	((Light*)models[3])->setPosition(*camera->getPosition());
	models[11]->childs[39]->updateRotation(glm::vec3(0, deltaTime*40, 0));
	models[11]->childs[40]->updateRotation(glm::vec3(deltaTime *40, 0, 0));

	if (lockCameraHeight) {
		glm::vec3* camPos = camera->getPosition();
		camera->setPosition(glm::vec3(camPos->x, 1, camPos->z));
	}

	switch (moveMode) {
		case BEZIERS: {
			moveTimeBezier += moveDelta * deltaTime;
			models[11]->invalidate();
			if (seaHawkPoints.size() == 1) {
				moveTimeBezier = 1;
			}
			else if (moveTimeBezier >= static_cast<int>(seaHawkPoints.size() - 1) / 3 || moveTimeBezier <= 0) {
				moveDelta *= -1;
			}
			break;
		}
		case LINES:
		default: {
			moveTimeLines += moveDelta * deltaTime;
			models[11]->invalidate();
			if (seaHawkPoints.size() == 1) {
				moveTimeLines = 1;
			} else if (moveTimeLines >= seaHawkPoints.size() || moveTimeLines <= 1 ) {
				moveDelta *= -1;
			}
			break;
		}
	}



	for (int i = 0; i < flickeringLights.size(); i++) {
		if (flickeringLights[i].duration <= 0) {
			flickeringLights[i].duration = Utils::floatRand(flickeringLights[i].maxFrequency, 0);
			flickeringLights[i].light->enabled = !flickeringLights[i].light->enabled;
			flickeringLights[i].light->invalidate();
		}
		flickeringLights[i].duration -= deltaTime;
	}

	for (int i = 0; i < treeGrowQueue.size(); i++) {
		if (treeGrowQueue[i]->getScale()->x < 0.8f) {
			treeGrowQueue[i]->updateScale(glm::vec3(0.05f));
		} else {
			treeGrowQueue.erase(std::remove(treeGrowQueue.begin(), treeGrowQueue.end(), treeGrowQueue[i]), treeGrowQueue.end());
			i--;
		}
	}

	bool filterShrink = false;
	for (int i = 0; i < treeShrinkQueue.size(); i++) {
		if (treeShrinkQueue[i]->getScale()->x > 0) {
			treeShrinkQueue[i]->updateScale(glm::vec3(-0.05f));
		} else {
			filterShrink = true;
		}
	}

	if (filterShrink) {
		for (GameObject* tree : treeShrinkQueue) {
			if (tree->getScale()->x <= 0) {
				treeShrinkQueue.erase(std::remove(treeShrinkQueue.begin(), treeShrinkQueue.end(), tree), treeShrinkQueue.end());
				models.erase(std::remove(models.begin(), models.end(), tree), models.end());
				indexUsageMap[((Model*)tree)->getId()] = false;
				delete tree;
				break;
			}
		}
	}
}

void AssimpLoaderScene::drawDebugElement()
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
		ImGui::End();
	}


	ImGui::Begin("Scene Debugger");
	ImGui::Checkbox("Lock camera height", &lockCameraHeight);
	ImGui::Text("Click modes");
	bool _treeMode = clickMode == AssimpLoaderSceneClickMode::TREEMODE;
	if (ImGui::Checkbox("Tree", &_treeMode)) {
		clickMode = AssimpLoaderSceneClickMode::TREEMODE;
	}

	bool _giftMode = clickMode == AssimpLoaderSceneClickMode::GIFTMODE;
	if (ImGui::Checkbox("Gift", &_giftMode)) {
		clickMode = AssimpLoaderSceneClickMode::GIFTMODE;
	}

	bool _orderMode = clickMode == AssimpLoaderSceneClickMode::ORDERMODE;
	if (ImGui::Checkbox("OrderMode", &_orderMode)) {
		clickMode = AssimpLoaderSceneClickMode::ORDERMODE;
	}

	ImGui::Text("Movement modes");
	bool __LinesMode = moveMode == AssimpLoaderSceneMoveMode::LINES;
	if (ImGui::Checkbox("OrderMode (lines)", &__LinesMode)) {
		moveMode = AssimpLoaderSceneMoveMode::LINES;
	}
	bool __BeziersMode = moveMode == AssimpLoaderSceneMoveMode::BEZIERS;
	if (ImGui::Checkbox("OrderMode (beziers)", &__BeziersMode)) {
		moveMode = AssimpLoaderSceneMoveMode::BEZIERS;
	}

	ImGui::Text("Movement data");
	ImGui::DragFloat("moveTimeLines", &moveTimeLines, 1, 0, 100);
	ImGui::DragFloat("moveTimeBezier", &moveTimeBezier, 1, 0, 100);
	ImGui::DragFloat("moveDelta", &moveDelta, 1, 0, 100);
	float vectorSize = seaHawkPoints.size();
	ImGui::DragFloat("length", &vectorSize, 1, 0, 100);
	ImGui::End();
}

void AssimpLoaderScene::listen(MessageType messageType, void* object)
{
	if (messageType == MessageType::MouseButtonPressed) {
		int x = (int)((CallbackManager::CBButtonData*)object)->mousePos.x;
		int y = (int)((CallbackManager::CBButtonData*)object)->mousePos.y;

		// size of window
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);

		GLfloat depth;
		GLuint index; // identification

		int newy = height - y;
		glReadPixels(x, newy, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &depth);
		glReadPixels(x, newy, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_INT, &index);

		glm::vec3 pos = glm::unProject(glm::vec3(x, newy, depth), camera->getViewMatrix(), camera->getProjectionMartix(), glm::vec4(0, 0, width, height));

		if (index == 0) {
			return;
		}

		switch (clickMode) {
			case ORDERMODE: {
				pos.y = 0;
				seaHawkPoints.push_back(pos);
				break;
			}
			case GIFTMODE: {
				if (index == 1) {
					return;
				}

				GameObject* goToDeleteGift = getGameObjectByIndex(index, "*gift*");
				if (goToDeleteGift != nullptr) {
					std::vector<GameObject*>* directParentArray = &models;
					if (goToDeleteGift->parent != nullptr) {
						directParentArray = &(goToDeleteGift->parent->childs);
					}
					(*directParentArray).erase(std::remove((*directParentArray).begin(), (*directParentArray).end(), goToDeleteGift), (*directParentArray).end());
				}
				break;
			}
			case TREEMODE:
			default: {
				if (index == 1) {
					int freeIndex = getUnusedIndex(2, 254);
					if (freeIndex == -1) {
						return;
					}

					Model* newTree = ModelBuilder()
						.name("tree")
						.setMesh(meshManager.getMesh("tree"))
						.setShader(shaderPrograms[std::string("blinnShader")])
						.setPosition(pos)
						.setScale(glm::vec3(0))
						.setMaterial(&materialManager["tree"])
						.setBasicTransforms()
						.setId(freeIndex)
						.finish();
					indexUsageMap[freeIndex] = true;
					models.push_back(newTree);
					treeGrowQueue.push_back(newTree);
					return;
				}

				GameObject* goToDelete = getGameObjectByIndex(index, "*tree*");
				if (goToDelete != nullptr) {
					treeGrowQueue.erase(std::remove(treeGrowQueue.begin(), treeGrowQueue.end(), goToDelete), treeGrowQueue.end());
					treeShrinkQueue.push_back(goToDelete);
				}
				break;
			}
		}
	}
}