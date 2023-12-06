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

#include "Transforms/BezierTransform.h"
#include "Transforms/LineTransform.h"
#include "Transforms/PolyLineTransform.h"
#include "Transforms/PolyBezierTransform.h"

extern const float cubeVertexData[];
extern const float triangleVertexData[];
extern const float sphere[];
extern const float suziFlat[];
extern const float suziSmooth[];

class MoveScene : public Scene
{
protected:
	void createShaders();
	void createModels();
	float moveTime = 0.1f;
	float moveDelta = 0.1f;
	std::vector<glm::vec3> polyLinePoints;

	glm::mat4 A;
	glm::mat4x3 B;
	std::vector<glm::vec3> C;
	std::vector<glm::vec3> D;



public:
	MoveScene(GLFWwindow* window);
	~MoveScene();
	using Scene::tick;
	void tick(float deltaTime);
	using Scene::draw;
	//void draw();
	using Scene::drawDebugElement;
	void drawDebugElement();

	void listen(MessageType messageType, void* object);
};

