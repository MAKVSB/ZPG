#pragma once
#include "GlobalInclude.h"

#include <map>
#include <vector>
#include <string>


class ModelManager {
private:
	std::map<std::string, std::vector<float>> modelMap;
public:
	void registerModel(std::string modelName, std::vector<float> modelData);
	std::vector<float>* getModel(std::string modelName);
};