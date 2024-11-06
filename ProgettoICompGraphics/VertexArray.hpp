#pragma once

#include <cstdint>

class VertexArray {
private:
	static uint32_t generateBuffer();
public:
	const uint32_t id;

	VertexArray();
	~VertexArray();

	void linkAttrib(const uint32_t layout, const uint32_t numComponents, const uint32_t type, const uint32_t offset) const;
	void bind() const;
	void unbind() const;
};