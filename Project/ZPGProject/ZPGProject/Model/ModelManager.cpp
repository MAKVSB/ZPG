#include "ModelManager.h"

void ModelManager::registerModel(std::string modelName, std::vector<float> modelData)
{
	modelMap.insert(std::pair(modelName, modelData));
}

std::vector<float>* ModelManager::getModel(std::string modelName)
{
	return &modelMap[modelName];
}