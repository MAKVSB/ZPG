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
#include <vector>

class PolyLineTransformStatic
{
public:
	static glm::vec3 transformPartial(std::vector<glm::vec3> vectors, float parameter) {
		float vectorSize = (float)vectors.size();
		if (vectorSize <= 0) {
			return glm::vec3(0);
		}

		glm::vec3 lastFinishedPoint = vectors[0];
		parameter = glm::clamp(parameter, 0.0f, vectorSize);

		for (int i = 0; i < vectorSize; i++) {
			if (parameter > i) {
				if (parameter - i > 1) {
					lastFinishedPoint = vectors[i];
					continue;
				}
			}
			glm::vec3 nextVectorRelative = vectors[i] - lastFinishedPoint;
			return lastFinishedPoint + (parameter - i) * nextVectorRelative;
		}
		return glm::vec3(0);
	}

	static void transform(GameObject* object, std::vector<glm::vec3> vectors, float parameterBefore, float parameter) {
		glm::vec3 beforeMovement = transformPartial(vectors, parameterBefore);
		glm::vec3 currentMovement = transformPartial(vectors, parameter);
		object->updatePosition(currentMovement - beforeMovement);
	}
};

class PolyLineTransform : public Transform
{
private:
	std::vector<glm::vec3>* vectors;
	float* parameterPointer;
public:
	PolyLineTransform(std::vector<glm::vec3>* vectors, float* parameterPointer) {
		this->vectors = vectors;
		this->parameterPointer = parameterPointer;
	}

	glm::mat4 transform(glm::mat4 m = glm::mat4(1)) {
		return glm::translate(m,PolyLineTransformStatic::transformPartial(*vectors, *parameterPointer));
	}
};
