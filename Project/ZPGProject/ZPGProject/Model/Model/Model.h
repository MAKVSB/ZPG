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
#include "Model/GameObject/GameObject.h"
#include "Model/Material/Material.h"
#include "Model/Mesh/Mesh.h"


class Model : public GameObject
{
private:
	GLuint materialUBO = -1;
	glm::vec2 textureScale = glm::vec2(1, 1);
public:
	ShaderProgram* shader = nullptr;
	Mesh* mesh = nullptr;
	Material* material = nullptr;

	void setMesh(Mesh* mesh);
	void setMaterial(Material* m);
	void setShader(ShaderProgram* sp);
	void setTextureScale(glm::vec2 ts);

	virtual ~Model();

	using GameObject::draw;
	void draw() override;
	using GameObject::tick;
	void tick(float deltaTime);
	using GameObject::drawDebugElement;
	virtual void drawDebugElement();

	virtual bool isModel() { return true; };

};