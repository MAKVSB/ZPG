/**
 * @file HouseObjectGroup.h
 *
 * @brief Defines behaviour of group of objects inside DefaultScene scene.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "Model/GameObject.h"
#include "Observer.h"
#include <map>

class HouseObjectGroup : public GameObject, public Observer
{
public:
	int test = 0;
	std::string valuse;
	std::map<int, int>* keypressMap = new std::map<int, int>();

	void tick(double deltaTime);
	void draw();
	HouseObjectGroup();
	~HouseObjectGroup();

	void listen(MessageType messageType, void* object);
};

