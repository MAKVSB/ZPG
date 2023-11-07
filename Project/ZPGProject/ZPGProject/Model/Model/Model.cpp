#pragma once
#include "Model.h"

void Model::setMesh(Mesh* mesh)
{
	this->mesh = mesh;
}

void Model::setVertexData(std::vector<float>* vd, VertexDataFormat df)
{
	vertexData = vd;
	dataFormat = df;

	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData->size() * sizeof(float), vertexData->data(), GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	switch (dataFormat)
	{
	case POS3_NOR3:
		vertexLength = 6;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		break;
	}

	glBindVertexArray(0);
}

void Model::setIndices(std::vector<uint32_t> ind)
{
	indices = ind;
}

void Model::setMaterial(Material m)
{
	this->material = m;
}

void Model::setShader(ShaderProgram* sp) {
	shader = sp;
}

Model::~Model()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

GLuint Model::getVertexCount()
{
	return (int)vertexData->size() / vertexLength;
}

void Model::draw() {
	shader->uploadUniformLocation("modelMatrix", tc->transform());
	shader->uploadUniformLocation("material.r_a", material.r_a);
	shader->uploadUniformLocation("material.r_d", material.r_d);
	shader->uploadUniformLocation("material.r_s", material.r_s);
	shader->uploadUniformLocation("material.objectColor", material.objectColor);

	if (mesh == nullptr) {
		if (indices.empty()) {
			shader->useWrapper([&]() {
				glBindVertexArray(VAO);
				// draw triangles
				glDrawArrays(GL_TRIANGLES, 0, getVertexCount()); //mode,first,count
				glBindVertexArray(0);
				});
		}
		else {
			shader->useWrapper([&]() {
				glBindVertexArray(VAO);
				// draw triangles based on indexes
				glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, indices.data());
				glBindVertexArray(0);
				});
		}
	}
	else {
		mesh->draw(*shader);
	}

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
		ImGui::DragFloat3("Position", glm::value_ptr(*position), 0.1f, -100.0f, 100.0f);

		// rotation
		ImGui::DragFloat3("Rotation", glm::value_ptr(*rotation), 0.1f, -100.0f, 100.0f);

		// scale
		ImGui::DragFloat3("Scale", glm::value_ptr(*scale), 0.1f, -100.0f, 100.0f);
		material.drawDebugElement();
		//// Light strength
		//if (ImGui::DragFloat("Strength", &lightStrength, 1, 0.0f, 100.0f)) {
		//	invalidate();
		//}

		//// Light strength
		//if (ImGui::DragFloat("Cutoff", &cutoff, 10, 0.0f, 360.0f)) {
		//	invalidate();
		//}

		////color
		//if (ImGui::ColorEdit3("color", glm::value_ptr(lightColor))) {
		//	invalidate();
		//}

		GameObject::drawDebugElement();
		ImGui::TreePop();
	}

	// End the window
	ImGui::End();
}