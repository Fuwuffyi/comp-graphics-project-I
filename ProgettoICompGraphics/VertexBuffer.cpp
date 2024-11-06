#include "VertexBuffer.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

VertexBuffer::VertexBuffer(const std::vector<Vertex>& vertices, const bool dynamic)
:
	SimpleBuffer(GL_ARRAY_BUFFER, dynamic)
{
	glBufferData(this->type, static_cast<int64_t>(vertices.size() * sizeof(uint32_t)), vertices.data(), dynamic ? GL_DYNAMIC_DRAW : GL_STATIC_DRAW);
}
