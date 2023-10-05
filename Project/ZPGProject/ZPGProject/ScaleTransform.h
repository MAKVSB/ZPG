#pragma once
#include "GlobalInclude.h"

#include "Transform.h"

class ScaleTransform : public Transform
{
private:
	glm::vec3* scaleVector;
public:
	ScaleTransform(glm::vec3* vector) {
		scaleVector = vector;
	}

	glm::mat4 transform(glm::mat4 m = glm::mat4(1)) {
		return glm::scale(m, *scaleVector);
	}
};