#pragma once

#include <array>
#include <vector>

#include "Vertex.hpp"

class BoundingBox {
private:
	/*
	* Contains the vertices of the bounding box for ease of 
	* use with objects that are transformed by matrices.
	*/
	std::array<glm::vec2, 4> boxVerts;

public:
	BoundingBox(const std::vector<Vertex>& vertices);
	BoundingBox(const std::array<glm::vec2, 4> _boxVerts);

	BoundingBox transform(const glm::mat4& transformationMatrix) const;

	bool checkCollisions(const BoundingBox& other) const;
};