#pragma once
#include "Model/Model/Model.h"

class Skybox : public Model {
private:
	Mesh meshData = Mesh();
	std::vector<float> points = {
		-1, -1, 1,
		-1, 1, 1,
		1, 1, 1,
		1, -1, 1,
		-1, -1, -1,
		-1, 1, -1,
		1, -1, -1,
		1, 1, -1
	};

	std::vector<uint32_t> indices = {
		//back
		0, 1, 2,
		0, 2, 3,
		// left
		0, 1, 4,
		5, 4, 1,
		// right
		3, 2, 6,
		7, 6, 2,
		// top
		2, 1, 5,
		2, 7, 5,
		// bottom
		3, 0, 4,
		3, 6, 4,
		// front 
		4, 5, 7,
		4, 7, 6,
	};

public:
	Skybox();
	using Model::draw;
	void draw();
	void drawDebugElement();
};