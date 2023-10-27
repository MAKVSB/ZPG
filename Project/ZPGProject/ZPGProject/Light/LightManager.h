#pragma once
#include "GlobalInclude.h"
#include "Observer.h"
#include "Light.h"
#include "ShaderProgram/ShaderProgram.h"

constexpr auto MAX_LIGHTS = 10;

class LightManager : public Observer, public Observable
{
private:
	std::vector<Light*> lights;
	GLuint lightsUBO;

public:
	LightManager();
	void attachShader(ShaderProgram* sp);
	void updateLightReferences(std::vector<GameObject*> gameObjects);
	virtual void listen(MessageType messageType, void* object) override;
};

