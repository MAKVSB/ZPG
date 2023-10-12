#pragma once
#include "Model/GameObject.h"
#include "Observer.h"

class HouseObjectGroup : public GameObject, public Observer
{
	int xDir = 0;
	int yDir = 0;
public:
	void tick(double deltaTime);
	void draw();
	HouseObjectGroup();
	~HouseObjectGroup();

	void listen(MessageType messageType, void* object);
};

