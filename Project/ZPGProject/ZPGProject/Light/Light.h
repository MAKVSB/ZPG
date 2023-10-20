#pragma once
#include "GlobalInclude.h"
#include "Model/GameObject.h"
#include "Observer.h"

#define GET_SET_NOTIFY(type, name, member) \
    void set##name(type value) { \
        member = value; \
        notify(MessageType::LightChanged, this); \
    } \
    type get##name() { \
        return member; \
    }

enum class LightType {
	AMBIENT,
	POSITIONAL,
	DIRECTIONAL,
	SPOTLIGHT,
};

class Light : public GameObject, public Observable
{
private:
	glm::vec3 lightColor;
	glm::vec3 lightDirection;
	LightType lightType;
public:
	GET_SET_NOTIFY(glm::vec3, LightColor, lightColor)
	GET_SET_NOTIFY(glm::vec3, LightDirection, lightDirection)
	GET_SET_NOTIFY(LightType, LightType, lightType)


	using GameObject::tick;
	void tick(double deltaTime);
	using GameObject::draw;
	void draw();
};

