#pragma once

#include <cstdint>

class SimpleBuffer {
private:
	static uint32_t generateBuffer();
public:
	const uint32_t id;
	const uint32_t type;
	const bool isDynamic;

	SimpleBuffer(const uint32_t _type, const bool dynamic = false);
	virtual ~SimpleBuffer();

	virtual void bind() const;
	virtual void unbind() const;
};