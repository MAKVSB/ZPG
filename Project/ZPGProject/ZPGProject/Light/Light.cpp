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
	objectName += " Light (" + std::to_string((uintptr_t)this) + ")";
	if (ImGui::TreeNode(objectName.c_str())) {
		if (ImGui::DragFloat3("Position", glm::value_ptr(*position), 0.1f, -100.0f, 100.0f)) {
			invalidate();
		}
		if (ImGui::DragFloat3("Direction", glm::value_ptr(*rotation), 0.1f, -100.0f, 100.0f)) {
			invalidate();
		}
		if (ImGui::DragFloat3("Attenuation", glm::value_ptr(lightAttenuation), 0.1f, 0.0f, 100.0f)) {
			invalidate();
		}
		if (ImGui::DragFloat("Strength", &lightStrength, 1, 0.0f, 100.0f)) {
			invalidate();
		}
		if (ImGui::DragFloat("Cutoff", &cutoff, 10, 0.0f, 360.0f)) {
			invalidate();
		}
		if (ImGui::ColorEdit3("color", glm::value_ptr(lightColor))) {
			invalidate();
		}
		if (ImGui::Checkbox("enabled", &enabled)) {
			invalidate();
		}

		GameObject::drawDebugElement();
		ImGui::TreePop();
	}

	// End the window
	ImGui::End();
}

void Light::invalidate() {
	notify(MessageType::LightChanged, this);
	GameObject::invalidate();
}

LightStruct Light::getStruct() {
	LightStruct ls;
	ls.position = glm::vec4(*position, 0);
	ls.direction = glm::vec4(*rotation, 0);
	ls.color = enabled ? glm::vec4(lightColor, 0) : glm::vec4(0);
	ls.attenuation = glm::vec4(lightAttenuation, 0);
	ls.lightType = static_cast<float>(lightType);
	ls.lightStrength = lightStrength;
	ls.cutoff = cutoff;

	if (parent != nullptr) {
		glm::mat4 translatedMatrix = glm::translate(parent->tc->transform(), *position);
		ls.position = glm::vec4(glm::vec3(translatedMatrix[3]) / translatedMatrix[3][3], 0);
		ls.direction = glm::vec4(glm::mat3(translatedMatrix) * *rotation, 0);
	}

	return ls;
}