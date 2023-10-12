#pragma once
#include <string>
#include "Model/ModelLoader.h"
#include "Model/Model.h"

template <typename T, typename = std::enable_if_t<std::is_base_of<GameObject, T>::value>>
class GameObjectBuilder
{
protected:
	T* model;
public:
	GameObjectBuilder() {
		model = new T();
	};

	GameObjectBuilder* name(std::string name) {
		if (model == nullptr) {
			throw std::runtime_error("Cannot assign name before vertexes " + name);
		}
		model->name = name;
		return this;
	};

	GameObjectBuilder* setPosition(glm::vec3* pos) { model->setPosition(pos); return this; };
	GameObjectBuilder* setRotation(glm::vec3* rot) { model->setRotation(rot); return this; };
	GameObjectBuilder* setScale(glm::vec3* scl) { model->setScale(scl); return this; };

	GameObjectBuilder* setBasicTransforms() {
		model->tc->addTranlateTransform(model->getPosition()); //move relative to its center (when building object from multiple objects)
		model->tc->addRotationTransform(model->getRotation()); //rotate on place
		model->tc->addScaleTransform(model->getScale()); // scale down
		return this;
	};

	GameObjectBuilder* addChild(GameObject* child) {
		model->addChild(child);
		return this;
	};

	T* finish() { return model; };
};


class ModelBuilder : public GameObjectBuilder<Model>
{
public:
	template <typename T, std::size_t N>
	ModelBuilder* loadVertexesFromArray(const T(&dataArray)[N], VertexDataFormat vdf = VertexDataFormat::POS4_COL4);
	ModelBuilder* setShader(ShaderProgram* sp) { model->shader = sp; return this; };
};

template<typename T, std::size_t N>
inline ModelBuilder* ModelBuilder::loadVertexesFromArray(const T(&dataArray)[N], VertexDataFormat vdf)
{
	model->setVertexData(ModelLoader::convertToVector<float>(dataArray), vdf);
	return this;
}