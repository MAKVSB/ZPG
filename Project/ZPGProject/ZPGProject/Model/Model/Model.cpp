#pragma once
#include "Model.h"

void Model::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void Model::setMaterial(Material* m)
{
	this->material = m;
}

void Model::setShader(ShaderProgram* sp) {
	shader = sp;
}

void Model::setTextureScale(glm::vec2 ts)
{
	textureScale = ts;
}

void Model::setId(GLuint id)
{
	objectId = id;
}

GLuint Model::getId()
{
	return objectId;
}

Model::~Model()
{
}

void Model::draw() {
	shader->uploadUniformLocation("modelMatrix", tc->transform());

	if (material != nullptr) {
		shader->uploadUniformLocation("material.r_a", material->r_a);
		shader->uploadUniformLocation("material.r_d", material->r_d);
		shader->uploadUniformLocation("material.r_s", material->r_s);
		shader->uploadUniformLocation("material.objectColor", material->objectColor);

		if (material->texture.bindTexture()) {
			shader->uploadUniformLocation("textureSet", 1);
			shader->uploadUniformLocation("textureUnitID", 0);
			shader->uploadUniformLocation("textureScaler", textureScale);
		}
		else {
			shader->uploadUniformLocation("textureSet", 0);
		}
	} else {
		Material m = Material();
		shader->uploadUniformLocation("material.r_a", m.r_a);
		shader->uploadUniformLocation("material.r_d", m.r_d);
		shader->uploadUniformLocation("material.r_s", m.r_s);
		shader->uploadUniformLocation("material.objectColor", m.objectColor);
		shader->uploadUniformLocation("textureSet", 0);
	}

	glStencilFunc(GL_ALWAYS, objectId, 0xFF);

	mesh->draw(*shader);

	GameObject::draw();
}

void Model::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
}

void Model::drawDebugElement() {
	ImGui::Begin("Object Debugger");
	std::string objectName(name);
	objectName += "Model (" + std::to_string((uintptr_t)this) + ")";
	if (ImGui::TreeNode(objectName.c_str())) {
		// position
		ImGui::DragFloat3("Position", glm::value_ptr(*position), 1, -100.0f, 100.0f);

		// rotation
		ImGui::DragFloat3("Rotation", glm::value_ptr(*rotation), 1, -100.0f, 100.0f);

		// scale
		ImGui::DragFloat3("Scale", glm::value_ptr(*scale), 1, -100.0f, 100.0f);
		if (material != nullptr) {
			material->drawDebugElement();
		}

		GameObject::drawDebugElement();
		ImGui::TreePop();
	}

	// End the window
	ImGui::End();
}