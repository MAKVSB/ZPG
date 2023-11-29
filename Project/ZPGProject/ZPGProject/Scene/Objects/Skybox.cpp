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

void Skybox::drawDebugElement() {
	ImGui::Begin("Object Debugger");
	std::string objectName(name);
	objectName += "Skybox (" + std::to_string((uintptr_t)this) + ")";
	if (ImGui::TreeNode(objectName.c_str())) {
		if (material != nullptr) {
			material->drawDebugElement();
		}
		GameObject::drawDebugElement();
		ImGui::TreePop();
	}

	// End the window
	ImGui::End();
}