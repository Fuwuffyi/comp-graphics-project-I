#include "ElementBuffer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

ElementBuffer::ElementBuffer(const std::vector<uint32_t>& indices, const bool dynamic)
	:
	SimpleBuffer(GL_ELEMENT_ARRAY_BUFFER, dynamic)
{
	glBufferData(this->type, static_cast<int64_t>(indices.size() * sizeof(uint32_t), indices.data(), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}