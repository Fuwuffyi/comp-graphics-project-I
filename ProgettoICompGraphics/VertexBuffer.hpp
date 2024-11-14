#pragma once

#include "SimpleBuffer.hpp"

#include <vector>

struct Vertex;

class VertexBuffer : public SimpleBuffer {
public:
	VertexBuffer(const std::vector<Vertex>& vertices, const bool dynamic = false);
};