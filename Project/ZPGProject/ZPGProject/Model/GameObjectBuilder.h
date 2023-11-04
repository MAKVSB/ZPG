/**
 * @file GameObjectBuilder.h
 *
 * @brief Builder for model class. Allows safe building of scene objects.
 *
 * @author Daniel Makovsky
 *
 * @year 2023
 **/

#pragma once
#include <string>
#include "Model/ModelLoader.h"
#include "Model/Model.h"

class ModelBuilder;

template <class BT, typename T, typename = std::enable_if_t<std::is_base_of<GameObject, T>::value>>
class GameObjectBuilderSpec
{
protected:
	T* model;
public:
	GameObjectBuilderSpec() {
		model = new T();
	};

	BT& name(std::string name) {
		if (model == nullptr) {
			throw std::runtime_error("Cannot assign name before vertexes " + name);
		}
		model->name = name;
		return static_cast<BT&>(*this);
	};

	BT& setPosition(glm::vec3 pos) { model->setPosition(pos); return static_cast<BT&>(*this); };
	BT& setRotation(glm::vec3 rot) { model->setRotation(rot); return static_cast<BT&>(*this); };
	BT& setScale(glm::vec3 scl) { model->setScale(scl); return static_cast<BT&>(*this); };

	BT& addTransform(Transform* t) { model->tc->add(t); return  static_cast<BT&>(*this); };
	BT& setBasicTransforms() {
		model->tc->addScaleTransform(model->getScale());
		model->tc->addRotationTransform(model->getRotation());
		model->tc->addTranlateTransform(model->getPosition());
		return static_cast<BT&>(*this);
	};

	BT& addChild(GameObject* child) {
		model->addChild(child);
		return static_cast<BT&>(*this);
	};

	T* finish() { return model; };
};

template <typename T, typename = std::enable_if_t<std::is_base_of<GameObject, T>::value>>
class GameObjectBuilder : public GameObjectBuilderSpec<GameObjectBuilder<T>, T> {};

template <class BT>
class ModelBuilderSpec : public GameObjectBuilderSpec<ModelBuilder, Model>
{
public:
	BT& setVertexData(std::vector<float>* modelData, VertexDataFormat df = VertexDataFormat::POS3_NOR3) { model->setVertexData(modelData, df); return static_cast<BT&>(*this); };
	BT& setShader(ShaderProgram* sp) { model->setShader(sp); return static_cast<BT&>(*this); };
	BT& setMaterial(Material m) { model->setMaterial(m); return static_cast<BT&>(*this); };
	BT& setIndices(std::vector<uint32_t> ind) { model->setIndices(ind); return static_cast<BT&>(*this); };
};

class ModelBuilder : public ModelBuilderSpec<ModelBuilder> {};