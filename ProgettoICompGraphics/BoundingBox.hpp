#pragma once

#include <array>
#include <vector>

#include "Vertex.hpp"

/**
 * Class containing the bounding box of a given object.
 */
class BoundingBox {
private:
	/*
	* Contains the max/min values of the coordinates in this order:
	* minX
	* maxX
	* minY
	* maxY.
	*/
	std::array<float, 4> maxMinValues;

public:
	/**
	 * Constructor for an axis aligned bounding box.
	 * 
	 * \param vertices The vertices to calculate the bounding box size from.
	 */
	BoundingBox(const std::vector<Vertex>& vertices);

	/**
	 * Creates a new bounding box given a transformation matrix.
	 * 
	 * \param transformationMatrix The transofrmation matrix to create the bounding box from.
	 * \return A new bounding box transformed based on the matrix.
	 */
	BoundingBox transform(const glm::mat4& transformationMatrix) const;

	/**
	 * Checks collision between this and another bounding box.
	 * 
	 * \param other The other bounding box to check collisions with.
	 * \return True if the two bounding boxes are colliding.
	 */
	bool checkCollisions(const BoundingBox& other) const;
};