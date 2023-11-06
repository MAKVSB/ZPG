#include "ModelLoader.h"

ModelLoader::ModelLoader(MeshManager* mM, VertexDataFormat vdf)
{
	meshManager = mM;
    vertexDataFormat = vdf;
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

    gameObject->setPosition(glm::vec3(0, 0, 0));
    gameObject->setScale(glm::vec3(scaling.x, scaling.y, scaling.z));
    //gameObject->setRotation(convertQuaternionToAxisRotations(rotation));
}



Model* ModelLoader::processMesh(aiMesh& mesh, aiNode& node, const aiScene& scene, std::string filePath) {
    Model* model = new Model(); //TODO memory leak 100% find a better way of assigning vertex data from Assimploader

    applyTransformations(node, model);

    std::vector<float>* vertexData = processVertices(mesh);
    std::vector<uint32_t>* indices = processIndices(mesh);

    model->setMesh(meshManager->registerMesh(filePath + std::to_string(++namingIndex), Mesh(*vertexData, *indices)));

    //const Material& mat = model.materials[mesh.mMaterialIndex];

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
        //if (mesh.mTextureCoords[0]) {
        //    vertexData->push_back(mesh.mTextureCoords[0][i].x);
        //    vertexData->push_back(mesh.mTextureCoords[0][i].y);
        //}
        //else {
        //    vertexData->push_back(0);
        //    vertexData->push_back(0);
        //}
        //vertexData->push_back(mesh.mTangents[i].x);
        //vertexData->push_back(mesh.mTangents[i].y);
        //vertexData->push_back(mesh.mTangents[i].z);
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
