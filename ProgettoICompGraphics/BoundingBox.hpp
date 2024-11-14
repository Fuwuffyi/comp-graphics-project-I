#pragma once

#include <array>
#include <vector>

#include "Vertex.hpp"

class BoundingBox {
private:
	/*
	* Contains the max/min values of the coordinates
	* minX
	* maxX
	* minY
	* maxY
	*/
	std::array<float, 4> maxMinValues;

public:
	BoundingBox(const std::vector<Vertex>& vertices);

	BoundingBox transform(const glm::mat4& transformationMatrix) const;

	bool checkCollisions(const BoundingBox& other) const;
};