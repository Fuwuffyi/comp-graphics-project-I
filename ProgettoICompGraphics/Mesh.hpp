#pragma once

#include "Camera.hpp"
#include "VertexArray.hpp"
#include "VertexBuffer.hpp"
#include "ElementBuffer.hpp"
#include "BoundingBox.hpp"

class Mesh {
protected:
	std::vector<Vertex> vertices;
	std::vector<uint32_t> indices;
public:
	const uint32_t drawType;
	const VertexArray vao;
	const VertexBuffer vbo;
	const ElementBuffer ebo;
	const BoundingBox aabb; // Axis aligned bounding box

	Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices, const uint32_t _drawType);
	const BoundingBox& getBoundingBox() const;
	virtual void draw() const;
};