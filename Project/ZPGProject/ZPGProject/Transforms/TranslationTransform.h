/**
 * @file translationTransform.h
 *
 * @brief Translation transform composite leaf
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "GlobalInclude.h"

#include "Transform.h"

class TranslationTransform : public Transform
{
private:
	glm::vec3* translateVector;
public:
	TranslationTransform(glm::vec3* vector) {
		translateVector = vector;
	}

	glm::mat4 transform(glm::mat4 m = glm::mat4(1)) {
		return glm::translate(m, *translateVector);
	}
};