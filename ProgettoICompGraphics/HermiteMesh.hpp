#pragma once

#include "Mesh.hpp"

struct HermiteVertex {
	Vertex vert;
	float tension;
	float bias;
	float continuity;
};

class HermiteMesh : public Mesh {
	private:
		static std::vector<Vertex> calculateHermiteVertices(const std::vector<HermiteVertex>& controlPoints, const uint32_t steps);
		static std::vector<uint32_t> generateHermiteIndices(const uint32_t vertexCount);
	public:
		HermiteMesh(const std::vector<HermiteVertex>& controlPoints, const uint32_t steps);
};