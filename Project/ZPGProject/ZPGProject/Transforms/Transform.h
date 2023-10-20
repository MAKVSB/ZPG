/**
 * @file Transform.h
 *
 * @brief Transform composite
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include "GlobalInclude.h"

class Transform
{
private:

public:
	virtual glm::mat4 transform(glm::mat4 m = glm::mat4(1)) = 0;

};