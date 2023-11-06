#include "Light.h"

void Light::tick(float deltaTime)
{
	GameObject::tick(deltaTime);
}

void Light::draw()
{
	GameObject::draw();
}

void Light::drawDebugElement() {
	ImGui::Begin("Object Debugger");
	std::string objectName(name);
	if (name.empty()) {
		switch (lightType)
		{
		case LightType::AMBIENT:
			objectName = "Ambient";
			break;
		case LightType::POINT:
			objectName = "Point";
			break;
		case LightType::DIRECTIONAL:
			objectName = "Directional";
			break;
		case LightType::SPOTLIGHT:
			objectName = "Spot";
			break;
		default:
			break;
		}
	}
	objectName += " Light (" + std::to_string((int)this) + ")";
	if (ImGui::TreeNode(objectName.c_str())) {
		// position
		if (ImGui::DragFloat3("Position", glm::value_ptr(*position), 0.1f, -100.0f, 100.0f)) {
			invalidate();
		}

		// direction
		if (ImGui::DragFloat3("Direction", glm::value_ptr(lightDirection), 0.1f, -100.0f, 100.0f)) {
			invalidate();
		}

		// attenuation
		if (ImGui::DragFloat3("Attenuation", glm::value_ptr(lightAttenuation), 0.1f, 0.0f, 100.0f)) {
			invalidate();
		}

		// Light strength
		if (ImGui::DragFloat("Strength", &lightStrength, 1, 0.0f, 100.0f)) {
			invalidate();
		}

		// Light strength
		if (ImGui::DragFloat("Cutoff", &cutoff, 10, 0.0f, 360.0f)) {
			invalidate();
		}

		//color
		if (ImGui::ColorEdit3("color", glm::value_ptr(lightColor))) {
			invalidate();
		}

		GameObject::drawDebugElement();
		ImGui::TreePop();
	}

	// End the window
	ImGui::End();
}