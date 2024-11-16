#pragma once

#include "SimpleBuffer.hpp"

#include <vector>

/**
 * Forward declaration of the struct Vertex.
 */
struct Vertex;

/**
 * Class to hold the information of a VertexBuffer (the vertices of an object).
 */
class VertexBuffer : public SimpleBuffer {
public:
	/**
	 * Constructor for the vertex buffer.
	 *
	 * \param vertices The vertices to save in the GPU buffer.
	 * \param dynamic Flag to check if the data can be overwritten.
	 */
	VertexBuffer(const std::vector<Vertex>& vertices, const bool dynamic = false);
};