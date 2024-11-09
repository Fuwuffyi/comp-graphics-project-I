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
		static std::vector<Vertex> calculateHermiteVertices(const std::vector<HermiteVertex>& controlPoints, const uint32_t steps, const bool loop);
		static std::vector<uint32_t> generateHermiteIndices(const uint32_t vertexCount, const bool loop);
	public:
		HermiteMesh(const std::vector<HermiteVertex>& controlPoints, const uint32_t steps, const bool loop = true);
};