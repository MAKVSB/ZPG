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
#include <vector>

class PolyBezierTransformStatic
{
public:
	static glm::mat4 calculateRotation(glm::mat4 coefs, std::vector<glm::vec3> pointsVector, float t, float smooth = 0) {
		int i = 0;

		// Limit t to prevent going beyond the last cubic
		if (t > static_cast<float>(pointsVector.size() - 1) / 3) {
			t = static_cast<float>(pointsVector.size() - 1) / 3;
		}

		while (t > 1) {
			i += 3;
			t -= 1;
		}

		glm::mat4x3 points = glm::mat4x3(
			pointsVector[i + 0],
			pointsVector[i + 1],
			pointsVector[i + 2],
			pointsVector[i + 3]
		);

		if (smooth > 0 && i > 0) {
			// Move the second control point in the same direction as the previous control point
			glm::vec3 currentControlPoint = pointsVector[i];
			glm::vec3 previousControlPoint = pointsVector[i - 1];
			glm::vec3 futureControlpoint = pointsVector[i + 1];
			glm::vec3 lastControlVector = currentControlPoint - previousControlPoint;
			glm::vec3 movedControlpoint = futureControlpoint + lastControlVector * glm::vec3(1 + smooth);
			points[1] = movedControlpoint;
		}

		// Calculate the derivative of the Bezier curve
		glm::vec4 derivParams = glm::vec4(3 * t * t, 2 * t, 1, 0.0f);
		glm::vec3 derivative = derivParams * coefs * glm::transpose(points);
		derivative = glm::normalize(derivative);

		// Use the derivative as the rotation axis
		glm::mat4 rotationMatrix = glm::mat4(1.0f);
		rotationMatrix = glm::rotate(rotationMatrix, glm::radians(derivative.y * 90.0f), glm::vec3(0, 0, derivative.x));
		//rotationMatrix = glm::rotate(rotationMatrix, glm::radians(derivative.x * 90.0f), glm::vec3(derivative.y, 0, 0));
		//rotationMatrix = glm::rotate(rotationMatrix, glm::radians(glm::length(derivative) * 90.0f), glm::vec3(0, derivative.y, 0));

		return rotationMatrix;
	}

	static glm::vec3 transformPartial(glm::mat4 coefs, std::vector<glm::vec3> pointsVector, float t, float smooth = 0 /*od 0 do 1*/) {
		int i = 0;

		if (pointsVector.size() < 4) {
			return glm::vec3(0);
		}

		// Limit t to prevent going beyond the last cubic
		if (t > static_cast<int>(pointsVector.size() - 1) / 3) {
			t = (static_cast<int>(pointsVector.size() - 1) / 3) - 0.01f;
		}

		while (t > 1) {
			i += 3;
			t -= 1;
		}

		glm::mat4x3 points = glm::mat4x3(
			pointsVector[i + 0],
			pointsVector[i + 1],
			pointsVector[i + 2],
			pointsVector[i + 3]
		);

		if (smooth > 0 && i > 0) {
			// move the second cubicppint in the same direction of previous cubicpoint
			glm::vec3 currentControlPoint = pointsVector[i];
			glm::vec3 previousControlPoint = pointsVector[i - 1];
			glm::vec3 futureControlpoint = pointsVector[i + 1];
			glm::vec3 lastControlVector = currentControlPoint - previousControlPoint;
			glm::vec3 movedControlpoint = futureControlpoint + lastControlVector * glm::vec3(1 + smooth);
			points[1] = movedControlpoint;
		}

		glm::vec4 parameters = glm::vec4(t * t * t, t * t, t, 1.0f);
		return parameters * coefs * glm::transpose(points);
	}
	static void transform(GameObject* object, glm::mat4 coefs, std::vector<glm::vec3> pointsVector, float parameterBefore, float parameter, float smooth = 0 /*od 0 do 1*/) {
		glm::vec3 beforeMovement = transformPartial(coefs, pointsVector, parameterBefore, smooth);
		glm::vec3 currentMovement = transformPartial(coefs, pointsVector, parameter, smooth);
		object->updatePosition(currentMovement - beforeMovement);
	}
};

class PolyBezierTransform : public Transform
{
private:
	glm::mat4* coefs;
	std::vector<glm::vec3>* pointsVector;
	float* parameterPointer;
	float smooth;
public:
	PolyBezierTransform(glm::mat4* coefs, std::vector<glm::vec3>* pointsVector, float* parameterPointer, float smooth = 0 /*od 0 do 1*/) {
		this->coefs = coefs;
		this->pointsVector = pointsVector;
		this->parameterPointer = parameterPointer;
		this->smooth = smooth;
	}

	glm::mat4 transform(glm::mat4 m = glm::mat4(1)) {
		m = m * glm::translate(m, PolyBezierTransformStatic::transformPartial(*coefs, *pointsVector, *parameterPointer, smooth));
		m = m * PolyBezierTransformStatic::calculateRotation(*coefs, *pointsVector, *parameterPointer, 0);
		return m;
	}
};