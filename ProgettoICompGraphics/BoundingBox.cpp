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

BoundingBox::BoundingBox(const std::array<glm::vec2, 4> _boxVerts)
:
	boxVerts(_boxVerts)
{}

BoundingBox BoundingBox::transform(const glm::mat4& transformationMatrix) const {
	std::array<glm::vec2, 4> verts;
	const glm::vec4 transformed0 = glm::vec4(this->boxVerts[0], 0.0f, 0.0f) * transformationMatrix;
	const glm::vec4 transformed1 = glm::vec4(this->boxVerts[1], 0.0f, 0.0f) * transformationMatrix;
	const glm::vec4 transformed2 = glm::vec4(this->boxVerts[2], 0.0f, 0.0f) * transformationMatrix;
	const glm::vec4 transformed3 = glm::vec4(this->boxVerts[3], 0.0f, 0.0f) * transformationMatrix;
	verts[0] = glm::vec2(transformed0.x, transformed0.y);
	verts[1] = glm::vec2(transformed1.x, transformed1.y);
	verts[2] = glm::vec2(transformed2.x, transformed2.y);
	verts[3] = glm::vec2(transformed3.x, transformed3.y);
	return BoundingBox(verts);
}

bool BoundingBox::checkCollisions(const BoundingBox& other) const {
	// TODO:
	return true;
}