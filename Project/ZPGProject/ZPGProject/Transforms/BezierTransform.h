/**
 * @file bezierTransform.h
 *
 * @brief Bezier transform composite leaf
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "GlobalInclude.h"

#include "Transform.h"

class BezierTransformStatic
{
public:
	static glm::vec3 transformPartial(glm::mat4 coefs, glm::mat4x3 points, float t) {
		glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
		return parameters * coefs * glm::transpose(points);
	}
	static void transform(GameObject* object, glm::mat4 coefs, glm::mat4x3 points, float parameterBefore, float parameter) {
		glm::vec3 beforeMovement = transformPartial(coefs, points, parameterBefore);
		glm::vec3 currentMovement = transformPartial(coefs, points, parameter);
		object->updatePosition(currentMovement - beforeMovement);
	}
};

class BezierTransform : public Transform
{
private:
	glm::mat4* coefs;
	glm::mat4x3* points;
	float* parameterPointer;
public:
	BezierTransform(glm::mat4* coefs, glm::mat4x3* points, float* parameterPointer) {
		this->coefs = coefs;
		this->points = points;
		this->parameterPointer = parameterPointer;
	}

	glm::mat4 transform(glm::mat4 m = glm::mat4(1)) {
		return glm::translate(m, BezierTransformStatic::transformPartial(*coefs, *points, *parameterPointer));
	}
};