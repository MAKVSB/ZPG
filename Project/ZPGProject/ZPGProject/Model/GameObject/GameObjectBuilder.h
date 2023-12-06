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
#include "Model/Model/ModelLoader.h"
#include "Model/Model/Model.h"
#include "Model/Mesh/Mesh.h"

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
		model->setBasicTransforms();
		return static_cast<BT&>(*this);
	};

	BT& addChild(GameObject* child) {
		model->addChild(child);
		return static_cast<BT&>(*this);
	};

	BT& setId(GLuint id) { model->setId(id); return static_cast<BT&>(*this); };

	T* finish() { return model; };
};

template <typename T, typename = std::enable_if_t<std::is_base_of<GameObject, T>::value>>
class GameObjectBuilder : public GameObjectBuilderSpec<GameObjectBuilder<T>, T> {};

template <class BT>
class ModelBuilderSpec : public GameObjectBuilderSpec<ModelBuilder, Model>
{
public:
	BT& setShader(ShaderProgram* sp) { model->setShader(sp); return static_cast<BT&>(*this); };
	BT& setMaterial(Material* m) { model->setMaterial(m); return static_cast<BT&>(*this); };
	BT& setMesh(Mesh* mesh) { model->setMesh(mesh); return static_cast<BT&>(*this); };
	BT& setTextureScale(glm::vec2 ts) { model->setTextureScale(ts); return static_cast<BT&>(*this); };
};

class ModelBuilder : public ModelBuilderSpec<ModelBuilder> {};