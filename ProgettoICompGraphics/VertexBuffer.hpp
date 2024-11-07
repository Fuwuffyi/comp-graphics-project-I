#pragma once

#include "SimpleBuffer.hpp"
#include "Vertex.hpp"

#include <vector>

class VertexBuffer : public SimpleBuffer {
public:
	VertexBuffer(const std::vector<Vertex>& vertices, const bool dynamic = false);
};