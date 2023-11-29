#pragma once
#include "GlobalInclude.h"
#include "Model/GameObject/GameObject.h"
#include "Observer.h"

#define GET_SET(type, name, member) \
    void set##name(type value) { \
        member = value; \
		invalidate(); \
    } \
    type get##name() { \
        return member; \
    }

struct LightStruct {
	glm::vec4 position;
	glm::vec4 direction;
	glm::vec4 color;
	glm::vec4 attenuation;
	float lightType;
	float lightStrength;
	float cutoff;
};

enum class LightType {
	AMBIENT,
	POINT,
	DIRECTIONAL,
	SPOTLIGHT,
};

class Light : public GameObject, public Observable
{
private:
	glm::vec3 lightColor = glm::vec3(1);
	glm::vec3 lightDirection = glm::vec3(0);
	glm::vec3 lightAttenuation = glm::vec3(1.0, 2.0 / 3.0, 2.0 / 1.0);
	LightType lightType = LightType::AMBIENT;
	float lightStrength = 64;
	float cutoff = 60;
public:
	GET_SET(glm::vec3, LightColor, lightColor)
	GET_SET(glm::vec3, LightDirection, lightDirection)
	GET_SET(glm::vec3, LightAttenuation, lightAttenuation)
	GET_SET(LightType, LightType, lightType)
	GET_SET(float, LightStrength, lightStrength)
	GET_SET(float, Cutoff, cutoff)
	bool enabled = true;

	using GameObject::tick;
	void tick(float deltaTime);
	using GameObject::draw;
	void draw();
	using GameObject::drawDebugElement;
	void drawDebugElement();

	virtual bool isLight() { return true; };
	void invalidate() {
		notify(MessageType::LightChanged, this);
	}

	LightStruct getStruct() {
		if (!enabled) {
			auto scutoff = cutoff;
		}

		LightStruct ls;
		ls.position = glm::vec4(*position, 0);
		ls.direction = glm::vec4(lightDirection, 0);
		ls.color = enabled ? glm::vec4(lightColor, 0) : glm::vec4(0);
		ls.attenuation = glm::vec4(lightAttenuation, 0);
		ls.lightType = static_cast<float>(lightType);
		ls.lightStrength = lightStrength;
		ls.cutoff = cutoff;
		return ls;
	}
};

