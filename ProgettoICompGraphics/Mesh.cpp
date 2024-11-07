#include "Mesh.hpp"

#include <GLFW/glfw3.h>

Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices) 
:
	vertices(vertices),
	indices(indices),
	vao(),
	vbo(this->vertices),
	ebo(this->indices)
{
	this->vao.bind();
	this->vbo.bind();
	this->ebo.bind();
	this->vao.linkAttrib(0, 2, GL_FLOAT, 0);
	this->vao.linkAttrib(1, 4, GL_FLOAT, 2 * sizeof(float));
	this->vao.unbind();
	this->vbo.unbind();
	this->ebo.unbind();
}

void Mesh::draw(const uint32_t drawType) const {
	this->vao.bind();
	glDrawElements(drawType, static_cast<int32_t>(indices.size()), GL_UNSIGNED_INT, 0);
}