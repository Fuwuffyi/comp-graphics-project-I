#pragma once

#include "SimpleBuffer.hpp"

#include <vector>

class ElementBuffer : public SimpleBuffer {
public:
	ElementBuffer(const std::vector<uint32_t>& indices, const bool dynamic = false);
};