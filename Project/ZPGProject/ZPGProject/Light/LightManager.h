#pragma once
#include "GlobalInclude.h"
#include "Observer.h"
#include "Light.h";

class LightManager : public Observer, public Observable
{
	std::vector<Light*> lights;

};

