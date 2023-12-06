/**
 * @file lineTransform.h
 *
 * @brief Line movement transform composite leaf
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "GlobalInclude.h"

#include "Transform.h"
#include "Model/GameObject/GameObject.h"

class LineTransformStatic
{
public:
	static glm::vec3 transformPartial(glm::vec3 vector, float parameter) {
		return parameter * vector;
	}

	static void transform(GameObject* object, glm::vec3 vector, float parameterBefore, float parameter) {
		glm::vec3 lastPositionUpdate = transformPartial(vector, parameterBefore);
		glm::vec3 currentPositionUpdate = transformPartial(vector, parameter);
		object->updatePosition(currentPositionUpdate - lastPositionUpdate);
	}
};

class LineTransform : public Transform
{
private:
	glm::vec3* vector;
	float* parameterPointer;
public:
	LineTransform(glm::vec3* vector, float* parameterPointer) {
		this->vector = vector;
		this->parameterPointer = parameterPointer;
	}

	glm::mat4 transform(glm::mat4 m = glm::mat4(1)) {
		return glm::translate(m, LineTransformStatic::transformPartial(*vector, *parameterPointer));
	}
};