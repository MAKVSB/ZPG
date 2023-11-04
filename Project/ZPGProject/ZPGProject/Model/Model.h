/**
 * @file Model.h
 *
 * @brief Scene model. Child of GameObject which extends its parent by texture data and actual rendering methods.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "GlobalInclude.h"

#include <iostream>
#include <vector>

#include "ShaderProgram/ShaderProgram.h"
#include "Model/GameObject.h"
#include "Material.h"

enum VertexDataFormat {
	POS3_NOR3,
};

class Model : public GameObject
{
private:
	GLuint VBO = -1;
	GLuint materialUBO = -1;
	VertexDataFormat dataFormat = POS3_NOR3;
	int vertexLength = -1;

public:
	GLuint VAO = -1;
	ShaderProgram* shader = nullptr;

	std::vector<float>* vertexData;
	std::vector<uint32_t> indices;
	Material material = Material();

	void setVertexData(std::vector<float>* vd, VertexDataFormat df = POS3_NOR3);
	void setIndices(std::vector<uint32_t> ind);
	void setMaterial(Material m);
	void setShader(ShaderProgram* sp);

	virtual ~Model();

	GLuint getVertexCount();
	using GameObject::draw;
	void draw() override;
	using GameObject::tick;
	void tick(float deltaTime);

	virtual bool isModel() { return true; };

};