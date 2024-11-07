#pragma once

#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "BoundingBox.hpp"

class Mesh {
private:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
public:
	const VertexArray vao;
	const VertexBuffer vbo;
	const ElementBuffer ebo;
	const BoundingBox aabb; // Axis aligned bounding box

	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);
	void draw(const uint32_t drawType) const;
};