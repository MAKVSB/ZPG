#include "Skybox.h"

Skybox::Skybox() {
	meshData.setVertexData(points, POS3);
	meshData.setIndices(indices);
	mesh = &meshData;
}

void Skybox::draw() {
	glDepthMask(GL_FALSE);
	Model::draw();
	glDepthMask(GL_TRUE);
}