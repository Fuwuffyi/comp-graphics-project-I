#pragma once

#include "Mesh.hpp"
#include "Vertex.hpp"

/**
 * Struct containing control points for a hermite curve.
 */
struct HermiteControlPoint {
	Vertex vert;
	float tension;
	float bias;
	float continuity;
};

/**
 * Mesh class rapresenting a full hermite curve.
 */
class HermiteMesh : public Mesh {
	private:
		/**
		 * Calculates the mesh's vertices based on given control points.
		 * 
		 * \param controlPoints The control points to generate the curve from.
		 * \param steps The amount of steps of interpolation taken between them.
		 * \param filled Flag to check if the curve should be filled or not.
		 * \return The vertices to build the mesh with.
		 */
		static std::vector<Vertex> calculateHermiteVertices(const std::vector<HermiteControlPoint>& controlPoints, const uint32_t steps, const bool filled = false);
		
		/**
		 * Calculates the mesh's indices for the hermite curve.
		 * 
		 * \param vertexCount The amount of vertices the curve is made off of.
		 * \param filled Flag to check if the curve should be filled or not.
		 * \return The vector of indices to build the mesh with.
		 */
		static std::vector<uint32_t> generateHermiteIndices(const uint32_t vertexCount, const bool filled = false);

		/**
		 * Function to calculate the tangent of a given control point.
		 * 
		 * \param controlPoints The vector of control points to calculate the tangent from.
		 * \param index The index to calculate the tangent of.
		 * \param isStart Flag to check if the vertex is start or end of a given part of the curve.
		 * \return The tangent value at that index.
		 */
		static glm::vec2 calculateTangent(const std::vector<HermiteControlPoint>& controlPoints, size_t index, bool isStart);
	public:
		/**
		 * Constructor for a HermiteMesh curve.
		 * 
		 * \param controlPoints The list of control points to generate the curve from.
		 * \param steps The interpolation steps taken between the control points.
		 * \param filled Flag to check if the curve should be filled or not.
		 */
		HermiteMesh(const std::vector<HermiteControlPoint>& controlPoints, const uint32_t steps, const bool filled = false);
};