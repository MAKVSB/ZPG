#include "Skybox.h"

Skybox::Skybox() {
	meshData.setVertexData(points);
	mesh = &meshData;
	tc->addTranlateTransform(position);
}

Skybox::~Skybox()
{
}

void Skybox::draw() {
	glDepthMask(GL_FALSE);
	auto test = tc->transform();
	shader->uploadUniformLocation("modelMatrix", test);
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
	glDepthMask(GL_TRUE);
	GameObject::draw();
}