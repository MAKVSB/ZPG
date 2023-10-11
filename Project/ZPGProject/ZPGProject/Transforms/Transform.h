#pragma once
#include "GlobalInclude.h"

class Transform
{
private:

public:
	virtual glm::mat4 transform(glm::mat4 m = glm::mat4(1)) = 0;

};