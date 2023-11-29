/**
 * @file ModelLoader.h
 *
 * @brief Helper methods and utilities for ModelBuilder class.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once

#include <vector>

//include static models
#include "Models/sphere.h"
#include "Models/suzi_flat.h"
#include "Models/suzi_smooth.h"
#include "Models/tree.h"
#include "Models/plain.h"
#include "Models/plain_indiced.h"
#include "Models/plain_textured.h"
#include "Models/bushes.h"
#include "Models/gift.h"


#include "Model/Mesh/MeshManager.h"
#include "Model.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <assimp/Importer.hpp>

static constexpr uint32_t importOpts = 
	aiProcess_OptimizeMeshes
	bitor aiProcess_JoinIdenticalVertices
	bitor aiProcess_Triangulate
	bitor aiProcess_CalcTangentSpace
	bitor aiProcess_GenSmoothNormals;

class ModelLoader
{
private:
	VertexDataFormat vertexDataFormat;
	MeshManager* meshManager;
	std::unordered_map<std::string, Material>* materialManager;
	ShaderProgram* shaderToUse = nullptr;

	int namingIndex = 0;

	std::vector<float>* processVertices(aiMesh& mesh);
	std::vector<uint32_t>* processIndices(aiMesh& mesh);
public:
	ModelLoader(MeshManager* mM, std::unordered_map<std::string, Material>* mm, VertexDataFormat vdf = POS3_NOR3);
	ModelLoader(MeshManager* meshM, std::unordered_map<std::string, Material>* matM, ShaderProgram* sp, VertexDataFormat vdf);
	void processMaterials(const aiScene& scene, std::string filePath);
	GameObject* loadModel(std::string filePath);
	void processNode(aiNode& node, const aiScene& scene, GameObject* parentModel, std::string filePath);
	void applyTransformations(aiNode& node, GameObject* gameObject);
	Model* processMesh(aiMesh& mesh, aiNode& node, const aiScene& scene, std::string filePath);
};