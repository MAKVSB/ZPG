#pragma once
#include "GlobalInclude.h"

#include <map>
#include <vector>
#include <string>
#include "Mesh.h"


class MeshManager {
private:
	std::unordered_map<std::string, Mesh> meshMap;
public:
	Mesh* registerMesh(std::string modelName, Mesh modelData);
	Mesh* getMesh(std::string modelName);
	~MeshManager();
};