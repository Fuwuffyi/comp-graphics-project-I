#include "BoundingBox.hpp"

#include <math.h>

BoundingBox::BoundingBox(const std::vector<Vertex>& vertices) {
	std::array<float, 4> maxMinValues;
	// Calculate max X and Y coordinates
	for (const Vertex& v : vertices) {
		maxMinValues[0] = std::min(maxMinValues[0], v.position.x);
		maxMinValues[1] = std::max(maxMinValues[1], v.position.x);
		maxMinValues[2] = std::min(maxMinValues[2], v.position.y);
		maxMinValues[3] = std::max(maxMinValues[3], v.position.y);
	}
	// Construct vertices from given vertices
	boxVerts[0] = glm::vec2(maxMinValues[1], maxMinValues[3]);
	boxVerts[1] = glm::vec2(maxMinValues[1], maxMinValues[2]);
	boxVerts[2] = glm::vec2(maxMinValues[0], maxMinValues[3]);
	boxVerts[3] = glm::vec2(maxMinValues[0], maxMinValues[2]);
}