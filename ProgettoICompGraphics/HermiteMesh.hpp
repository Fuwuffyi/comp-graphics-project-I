#pragma once

#include "Mesh.hpp"

struct HermiteControlPoint {
	Vertex vert;
	float tension;
	float bias;
	float continuity;
};

class HermiteMesh : public Mesh {
	private:
		static std::vector<Vertex> calculateHermiteVertices(const std::vector<HermiteControlPoint>& controlPoints, const uint32_t steps, const bool filled = false);
		static std::vector<uint32_t> generateHermiteIndices(const uint32_t vertexCount, const bool filled = false);

		static glm::vec2 calculateTangent(const std::vector<HermiteControlPoint>& controlPoints, size_t index, bool isStart);
	public:
		HermiteMesh(const std::vector<HermiteControlPoint>& controlPoints, const uint32_t steps, const bool filled = false);
};