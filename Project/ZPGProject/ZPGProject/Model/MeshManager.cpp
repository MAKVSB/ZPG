#include "MeshManager.h"

Mesh* MeshManager::registerMesh(std::string modelName, Mesh modelData)
{
	meshMap[modelName] = modelData;
	return &meshMap[modelName];
}

Mesh* MeshManager::getMesh(std::string modelName)
{
	return &meshMap[modelName];
}

MeshManager::~MeshManager()
{
	for (auto mesh : meshMap)
	{
		mesh.second.destroy();
	}
}
