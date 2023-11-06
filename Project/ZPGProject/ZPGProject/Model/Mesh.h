#pragma once
#include "GlobalInclude.h"

#include <vector>
#include <ShaderProgram/ShaderProgram.h>
#include "Utils.h"

enum VertexDataFormat {
	POS3_NOR3,
};

struct BoundingBox {
	glm::vec3 min = glm::vec3(0.0, 0.0, 0.0);
	glm::vec3 max = glm::vec3(0.0, 0.0, 0.0);
};

class Mesh {
private:
	GLuint VAO = -1;
	GLuint VBO = -1;
	VertexDataFormat dataFormat = VertexDataFormat::POS3_NOR3;
	int vertexLength = -1;

	GLuint getVertexCount();
	void calculateBoundingbox();
public:
	Mesh();
	Mesh(std::vector<float> vd, VertexDataFormat df = VertexDataFormat::POS3_NOR3);
	Mesh(std::vector<float> vd, std::vector<uint32_t> ind, VertexDataFormat df = VertexDataFormat::POS3_NOR3);
	template <typename T, std::size_t N>
	Mesh(const T(&dataArray)[N], VertexDataFormat df = VertexDataFormat::POS3_NOR3);
	template <typename T, std::size_t N, typename K, std::size_t M>
	Mesh(const T(&dataArray)[N], const K(&ind)[M], VertexDataFormat df = VertexDataFormat::POS3_NOR3);
	void destroy();

	std::vector<float> vertexData;
	std::vector<uint32_t> indices;
	BoundingBox boundingBox;

	void setVertexData(std::vector<float> vd, VertexDataFormat df = VertexDataFormat::POS3_NOR3);
	void setIndices(std::vector<uint32_t> ind);

	void draw(ShaderProgram& shader);
	void drawDebugElement();
};

template<typename T, std::size_t N>
inline Mesh::Mesh(const T(&dataArray)[N], VertexDataFormat df)
{
	setVertexData(Utils::convertToVector(dataArray));
}

template<typename T, std::size_t N, typename K, std::size_t M>
inline Mesh::Mesh(const T(&dataArray)[N], const K(&ind)[M], VertexDataFormat df)
{
	setVertexData(Utils::convertToVector(dataArray));
	setIndices(Utils::convertToVector(ind));
}
