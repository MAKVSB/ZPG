/**
 * @file SceneC5.h
 *
 * @brief Scene for showcasing light shaders.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "Scene/Scene.h"

#include "Transforms/PolyLineTransform.h"
#include "Transforms/PolyBezierTransform.h"

extern const float cubeVertexData[];
extern const float triangleVertexData[];
extern const float sphere[];
extern const float suziFlat[];
extern const float suziSmooth[];

enum AssimpLoaderSceneClickMode {
	TREEMODE,
	GIFTMODE,
	ORDERMODE,
};

enum AssimpLoaderSceneMoveMode {
	//LINE,
	LINES,
	//BEZIER,
	BEZIERS
};

class AssimpLoaderScene : public Scene, Observer
{
protected:
	void createShaders();
	void createModels();
public:

	struct FlickerLight {
		Light* light;
		float duration;
		float maxFrequency;
	};
	bool lockCameraHeight = true;
	std::vector<FlickerLight> flickeringLights;
	std::vector<GameObject*> treeGrowQueue;
	std::vector<GameObject*> treeShrinkQueue;
	AssimpLoaderSceneClickMode clickMode = AssimpLoaderSceneClickMode::TREEMODE;
	AssimpLoaderSceneMoveMode moveMode = AssimpLoaderSceneMoveMode::LINES;

	float moveTimeLines = 1;
	float moveTimeBezier = 0.1f;
	float moveDelta = 0.1f;
	glm::mat4 coefs = glm::mat4(
		glm::vec4(-1.0, 3.0, -3.0, 1.0),
		glm::vec4(3.0, -6.0, 3.0, 0),
		glm::vec4(-3.0, 3.0, 0, 0),
		glm::vec4(1, 0, 0, 0)
	);
	std::vector<glm::vec3> seaHawkPoints;

	AssimpLoaderScene(GLFWwindow* window);
	~AssimpLoaderScene();
	using Scene::tick;
	void tick(float deltaTime);
	using Scene::draw;
	//void draw();
	using Scene::drawDebugElement;
	void drawDebugElement();

	void listen(MessageType messageType, void* object);
};

