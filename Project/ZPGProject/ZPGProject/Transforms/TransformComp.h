#pragma once
#include "GlobalInclude.h"

#include "Transform.h"
#include "RotationTransform.h"
#include "ScaleTransform.h"
#include "TranslationTransform.h"

#include <vector>

class TransformComp : Transform
{
private:
	std::vector<Transform*> transformList;
public:
	glm::mat4 transform(glm::mat4 m = glm::mat4(1)) {
		for (Transform* element : transformList) {
			m = element->transform(m);
		}
  		return m;
	}

	void add(Transform* transform) {
		transformList.emplace_back(transform);
	}

	//Factory methods
	void resetTransformMatrix() {
		transformList.clear();
	}

	void addRotationTransform(glm::vec3* vec) {
		transformList.emplace_back(new RotationTransform(vec));
	}

	void addTranlateTransform(glm::vec3* vec) {
		transformList.emplace_back(new TranslationTransform(vec));
	}

	void addScaleTransform(glm::vec3* vec) {
		transformList.emplace_back(new ScaleTransform(vec));
	}
};