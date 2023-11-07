/**
 * @file OffsetRotator.h
 *
 * @brief Defines behaviour of group of objects inside Universe scene.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "Model/GameObject/GameObject.h"
#include "Observer.h"
#include <map>

class OffsetRotator : public GameObject
{
public:
	void tick(float deltaTime);
	void draw();
};

