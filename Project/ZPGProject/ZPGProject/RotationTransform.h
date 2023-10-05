#pragma once
#include "GlobalInclude.h"

#include "Transform.h"

class RotationTransform : public Transform
{
private:
	glm::vec3* rotationVector;
public:
	RotationTransform(glm::vec3* vector) {
		rotationVector = vector;
	}

	glm::mat4 transform(glm::mat4 m = glm::mat4(1)) {
		m = glm::rotate(m, (*rotationVector)[0], glm::vec3(1.0f, 0.0f, 0.0f));
		m = glm::rotate(m, (*rotationVector)[1], glm::vec3(0.0f, 1.0f, 0.0f));
		return glm::rotate(m, (*rotationVector)[2], glm::vec3(0.0f, 0.0f, 1.0f));
	}
};