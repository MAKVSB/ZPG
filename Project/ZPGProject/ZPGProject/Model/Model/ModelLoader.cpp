#include "ModelLoader.h"

#include <iostream>
#include <filesystem>

ModelLoader::ModelLoader(MeshManager* meshM, std::unordered_map<std::string, Material>* matM, VertexDataFormat vdf)
{
	meshManager = meshM;
    vertexDataFormat = vdf;
    materialManager = matM;
}

ModelLoader::ModelLoader(MeshManager* meshM, std::unordered_map<std::string, Material>* matM, ShaderProgram* sp, VertexDataFormat vdf)
{
    meshManager = meshM;
    vertexDataFormat = vdf;
    materialManager = matM;
    shaderToUse = sp;
}

void ModelLoader::processMaterials(const aiScene& scene, std::string fp) {
    std::filesystem::path filePath = fp;
    std::filesystem::path folderPath = filePath.parent_path();

    for (int i = 0; i < scene.mNumMaterials; i++) {
        Material materialData = Material();

        GLuint texIndex = 0;
        aiString path;
        aiReturn texFound = scene.mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);
        if (texFound == aiReturn_SUCCESS) {
            materialData.texture.loadTexture2D(folderPath.string() + "/" + path.C_Str(), true);
        }
        (*materialManager)[fp + std::to_string(i)] = materialData;
        auto test = "test";
    }
}

GameObject* ModelLoader::loadModel(std::string filePath)
{
    Assimp::Importer importer;
    const aiScene* aiscene = importer.ReadFile(filePath, importOpts);

    if (!aiscene) {
        throw std::runtime_error("Error loading model");
    }
    const aiScene& scene = *aiscene;

    if (scene.mFlags bitand AI_SCENE_FLAGS_INCOMPLETE or not scene.mRootNode) {
        throw std::runtime_error("Error loading model");
    }
    GLuint texIndex = 0;
    aiString path;
    aiReturn texFound = scene.mMaterials[1]->GetTexture(aiTextureType_DIFFUSE, texIndex, &path);

    processMaterials(scene, filePath);

    GameObject* model = new GameObject(); //TODO memory leak 100% find a better way of assigning vertex data from Assimploader
    applyTransformations(*scene.mRootNode, model);
    processNode(*scene.mRootNode, scene, model, filePath);
    return model;
}

void ModelLoader::processNode(aiNode& node, const aiScene& scene, GameObject* parentModel, std::string filePath)
{
    for (uint32_t i = 0; i < node.mNumMeshes; ++i) {
        aiMesh* mesh = scene.mMeshes[node.mMeshes[i]];
        parentModel->addChild(processMesh(*mesh, node, scene, filePath));
    }
    for (uint32_t i = 0; i < node.mNumChildren; ++i) {
        GameObject* model = new GameObject(); //TODO memory leak 100% find a better way of assigning vertex data from Assimploader
        applyTransformations(node, model);
        processNode(*(node.mChildren[i]), scene, model, filePath);
        parentModel->addChild(model);
    }
}

void ModelLoader::applyTransformations(aiNode& node, GameObject* gameObject) {
    aiMatrix4x4 transformationMatrix = node.mTransformation;
    // To access the individual components:
    aiVector3D scaling, position;
    aiQuaternion rotation;
    transformationMatrix.Decompose(scaling, rotation, position);

    gameObject->setPosition(glm::vec3(position.x, position.y, position.z));
    gameObject->setScale(glm::vec3(scaling.x, scaling.y, scaling.z));

    gameObject->setBasicTransforms();
}



Model* ModelLoader::processMesh(aiMesh& mesh, aiNode& node, const aiScene& scene, std::string filePath) {
    Model* model = new Model(); //TODO memory leak 100% find a better way of assigning vertex data from Assimploader

    applyTransformations(node, model);

    std::vector<float>* vertexData = processVertices(mesh);
    std::vector<uint32_t>* indices = processIndices(mesh);

    if (mesh.mMaterialIndex != 0) {
        model->setMaterial(&(*materialManager)[filePath + std::to_string(mesh.mMaterialIndex)]);
    }

    if (shaderToUse) {
        model->setShader(shaderToUse);
    }

    model->setMesh(meshManager->registerMesh(filePath + std::to_string(++namingIndex), Mesh(*vertexData, *indices, vertexDataFormat)));

    return model;
}

std::vector<float>* ModelLoader::processVertices(aiMesh& mesh) {
    std::vector<float>* vertexData = new std::vector<float>();
    for (uint32_t i = 0; i < mesh.mNumVertices; ++i)
    {
        vertexData->push_back(mesh.mVertices[i].x);
        vertexData->push_back(mesh.mVertices[i].y);
        vertexData->push_back(mesh.mVertices[i].z);
        vertexData->push_back(mesh.mNormals[i].x);
        vertexData->push_back(mesh.mNormals[i].y);
        vertexData->push_back(mesh.mNormals[i].z);

        if (vertexDataFormat == POS3_NOR3_TEX2) {
            if (mesh.HasTextureCoords(0)) {
                vertexData->push_back(mesh.mTextureCoords[0][i].x);
                vertexData->push_back(mesh.mTextureCoords[0][i].y);
            } else {
                vertexData->push_back(0);
                vertexData->push_back(0);
            }
        }
    }
    return vertexData;
}

std::vector<uint32_t>* ModelLoader::processIndices(aiMesh& mesh) {
    std::vector<uint32_t>* indices = new std::vector<uint32_t>();
    for (uint32_t i = 0; i < mesh.mNumFaces; ++i) {
        for (uint32_t j = 0; j < mesh.mFaces[i].mNumIndices; ++j) {
            indices->emplace_back(mesh.mFaces[i].mIndices[j]);
        }
    }
    return indices;
}
