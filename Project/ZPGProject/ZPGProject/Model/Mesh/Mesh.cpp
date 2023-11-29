#include "Mesh.h"

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector<float> vd, VertexDataFormat df)
{
	setVertexData(vd, df);
}

Mesh::Mesh(std::vector<float> vd, std::vector<uint32_t> ind, VertexDataFormat df)
{
	setVertexData(vd, df);
	setIndices(ind);
}

GLuint Mesh::getVertexCount()
{
	return (int)vertexData.size() / vertexLength;
}

void Mesh::calculateBoundingbox()
{
	for (std::size_t i = 0; i < vertexData.size(); i += vertexLength) {
		boundingBox.min.x = std::min(boundingBox.min.x, vertexData[i]);
		boundingBox.min.y = std::min(boundingBox.min.y, vertexData[i+1]);
		boundingBox.min.z = std::min(boundingBox.min.z, vertexData[i+2]);
		boundingBox.max.x = std::max(boundingBox.max.x, vertexData[i]);
		boundingBox.max.y = std::max(boundingBox.max.y, vertexData[i+1]);
		boundingBox.max.z = std::max(boundingBox.max.z, vertexData[i+2]);
	}
}

void Mesh::destroy()
{
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);
}

void Mesh::setVertexData(std::vector<float> vd, VertexDataFormat df)
{
	vertexData = vd;
	dataFormat = df;

	//vertex buffer object (VBO)
	VBO = 0;
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, vertexData.size() * sizeof(float), vertexData.data(), GL_STATIC_DRAW);

	//Vertex Array Object (VAO)
	VAO = 0;
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	switch (dataFormat)
	{
	case POS3_NOR3:
		vertexLength = 6;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		break;
	case POS3_NOR3_TEX2:
		vertexLength = 8;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)(6 * sizeof(float)));
		break;
	case POS3:
		vertexLength = 3;
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexLength * sizeof(float), (GLvoid*)0);
		break;
	}
	glBindVertexArray(0);
	calculateBoundingbox();
}

void Mesh::setIndices(std::vector<uint32_t> ind)
{
	indices = ind;
}

void Mesh::draw(ShaderProgram& shader)
{
	if (indices.empty()) {
		shader.useWrapper([&]() {
			glBindVertexArray(VAO);
			// draw triangles
			glDrawArrays(GL_TRIANGLES, 0, getVertexCount()); //mode,first,count
			glBindVertexArray(0);
		});
	}
	else {
		shader.useWrapper([&]() {
			glBindVertexArray(VAO);
			// draw triangles based on indexes
			glDrawElements(GL_TRIANGLES, (GLsizei)indices.size(), GL_UNSIGNED_INT, indices.data());
			glBindVertexArray(0);
		});
	}
}

void Mesh::drawDebugElement()
{
}
