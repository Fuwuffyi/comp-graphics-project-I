#include "Mesh.hpp"

#include "Vertex.hpp"

#include <glad/glad.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const uint32_t _drawType)
:
	vertices(vertices),
	indices(indices),
	drawType(_drawType),
	vao(),
	vbo(this->vertices),
	ebo(this->indices),
	aabb(this->vertices)
{
	this->vao.bind();
	this->vbo.bind();
	this->ebo.bind();
	// Link the vertice's attributes to slots: (0 = position, 1 = color)
	this->vao.linkAttrib(0, 2, GL_FLOAT, 0);
	this->vao.linkAttrib(1, 4, GL_FLOAT, 2 * sizeof(float));
	this->vao.unbind();
	this->vbo.unbind();
	this->ebo.unbind();
}

const BoundingBox& Mesh::getBoundingBox() const {
	return this->aabb;
}

void Mesh::draw() const {
	this->vao.bind();
	glDrawElements(this->drawType, static_cast<int32_t>(indices.size()), GL_UNSIGNED_INT, 0);
}