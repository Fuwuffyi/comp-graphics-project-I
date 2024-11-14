#include "BoundingBox.hpp"

#include <cmath>
#include <limits>

BoundingBox::BoundingBox(const std::vector<Vertex>& vertices) 
:
	maxMinValues({ std::numeric_limits<float>::max(), std::numeric_limits<float>::min(), std::numeric_limits<float>::max(), std::numeric_limits<float>::min() })
{
	for (const Vertex& v : vertices) {
		this->maxMinValues[0] = std::min(maxMinValues[0], v.position.x);
		this->maxMinValues[1] = std::max(maxMinValues[1], v.position.x);
		this->maxMinValues[2] = std::min(maxMinValues[2], v.position.y);
		this->maxMinValues[3] = std::max(maxMinValues[3], v.position.y);
	}
}

BoundingBox BoundingBox::transform(const glm::mat4& transformationMatrix) const {
	std::vector<Vertex> verts(4);
	const glm::vec4 transformed0 = transformationMatrix * glm::vec4(this->maxMinValues[0], this->maxMinValues[2], 0.0f, 0.0f);
	const glm::vec4 transformed1 = transformationMatrix * glm::vec4(this->maxMinValues[0], this->maxMinValues[3], 0.0f, 0.0f);
	const glm::vec4 transformed2 = transformationMatrix * glm::vec4(this->maxMinValues[1], this->maxMinValues[2], 0.0f, 0.0f);
	const glm::vec4 transformed3 = transformationMatrix * glm::vec4(this->maxMinValues[1], this->maxMinValues[3], 0.0f, 0.0f);
	verts[0] = Vertex{ glm::vec2(transformed0.x, transformed0.y), glm::vec4(0.0f) };
	verts[1] = Vertex{ glm::vec2(transformed1.x, transformed1.y), glm::vec4(0.0f) };
	verts[2] = Vertex{ glm::vec2(transformed2.x, transformed2.y), glm::vec4(0.0f) };
	verts[3] = Vertex{ glm::vec2(transformed3.x, transformed3.y), glm::vec4(0.0f) };
	return BoundingBox(verts);
}

bool BoundingBox::checkCollisions(const BoundingBox& other) const {
	// TODO: 
	return true;
}