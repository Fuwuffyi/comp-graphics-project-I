#include "BoundingBox.hpp"

#include <cmath>
#include <limits>

BoundingBox::BoundingBox(const std::vector<Vertex>& vertices) 
:
	maxMinValues({ std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity(), std::numeric_limits<float>::infinity(), -std::numeric_limits<float>::infinity() })
{
	for (const Vertex& v : vertices) {
		this->maxMinValues[0] = std::min(maxMinValues[0], v.position.x);	// 0 = minX
		this->maxMinValues[1] = std::max(maxMinValues[1], v.position.x);	// 1 = maxX
		this->maxMinValues[2] = std::min(maxMinValues[2], v.position.y);	// 2 = minY
		this->maxMinValues[3] = std::max(maxMinValues[3], v.position.y);	// 3 = maxY
	}
}

BoundingBox BoundingBox::transform(const glm::mat4& transformationMatrix) const {
	std::vector<Vertex> verts(4);
	const glm::vec4 transformed0 = transformationMatrix * glm::vec4(this->maxMinValues[0], this->maxMinValues[2], 0.0f, 1.0f);
	const glm::vec4 transformed1 = transformationMatrix * glm::vec4(this->maxMinValues[0], this->maxMinValues[3], 0.0f, 1.0f);
	const glm::vec4 transformed2 = transformationMatrix * glm::vec4(this->maxMinValues[1], this->maxMinValues[2], 0.0f, 1.0f);
	const glm::vec4 transformed3 = transformationMatrix * glm::vec4(this->maxMinValues[1], this->maxMinValues[3], 0.0f, 1.0f);
	verts[0] = Vertex{ glm::vec2(transformed0.x, transformed0.y), glm::vec4(0.0f) };
	verts[1] = Vertex{ glm::vec2(transformed1.x, transformed1.y), glm::vec4(0.0f) };
	verts[2] = Vertex{ glm::vec2(transformed2.x, transformed2.y), glm::vec4(0.0f) };
	verts[3] = Vertex{ glm::vec2(transformed3.x, transformed3.y), glm::vec4(0.0f) };
	return BoundingBox(verts);
}

bool BoundingBox::checkCollisions(const BoundingBox& other) const {
	const bool overlapX = this->maxMinValues[1] >= other.maxMinValues[0] && other.maxMinValues[1] >= this->maxMinValues[0];
	const bool overlapY = this->maxMinValues[3] >= other.maxMinValues[2] && other.maxMinValues[3] >= this->maxMinValues[2];
	return overlapX && overlapY;
}