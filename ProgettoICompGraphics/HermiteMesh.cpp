#include "HermiteMesh.hpp"

#include <glad/glad.h>

HermiteMesh::HermiteMesh(const std::vector<HermiteControlPoint>& controlPoints, const uint32_t steps, const bool filled)
:
    Mesh(
        HermiteMesh::calculateHermiteVertices(controlPoints, steps, filled),
        HermiteMesh::generateHermiteIndices(controlPoints.size() * steps + 1 + filled, filled),
        filled ? GL_TRIANGLE_FAN : GL_LINE_LOOP
    )
{}

glm::vec2 HermiteMesh::calculateTangent(const std::vector<HermiteControlPoint>& controlPoints, size_t index, bool isStart) {
    const HermiteControlPoint& point = controlPoints[index];
    glm::vec2 tangent;
    if (isStart) {
        // Start tangent calculation
        if (index == 0) {
            // Use the last control point as previous for a circular setup
            const HermiteControlPoint& prevPoint = controlPoints.back();
            tangent.x = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (point.vert.position.x - prevPoint.vert.position.x) * 0.5f;
            tangent.y = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (point.vert.position.y - prevPoint.vert.position.y) * 0.5f;
        }
        else {
            const HermiteControlPoint& prevPoint = controlPoints[index - 1];
            tangent.x = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (point.vert.position.x - prevPoint.vert.position.x) * 0.5f;
            tangent.y = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (point.vert.position.y - prevPoint.vert.position.y) * 0.5f;
        }
    } else {
        // End tangent calculation
        if (index == controlPoints.size() - 1) {
            // Use the first control point as next for a circular setup
            const HermiteControlPoint& nextPoint = controlPoints.front();
            tangent.x = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (nextPoint.vert.position.x - point.vert.position.x) * 0.5f;
            tangent.y = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (nextPoint.vert.position.y - point.vert.position.y) * 0.5f;
        }
        else {
            const HermiteControlPoint& nextPoint = controlPoints[index + 1];
            tangent.x = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (nextPoint.vert.position.x - point.vert.position.x) * 0.5f;
            tangent.y = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (nextPoint.vert.position.y - point.vert.position.y) * 0.5f;
        }
    }
    return tangent;
}

std::vector<Vertex> HermiteMesh::calculateHermiteVertices(const std::vector<HermiteControlPoint>& controlPoints, const uint32_t steps, const bool filled) {
    std::vector<Vertex> vertices(controlPoints.size() * steps + 1 + filled); // Preallocate memory
    // If filled shape, use first point as center
    if (filled) {
        vertices[0] = controlPoints[0].vert;
    }
    // Iterate through control points in pairs
    for (uint32_t i = filled; i < controlPoints.size(); ++i) {
        const uint32_t index0 = i;
        const uint32_t index1 = i == controlPoints.size() - 1 ? filled : i + 1;
        const HermiteControlPoint& p0 = controlPoints[index0];
        const HermiteControlPoint& p1 = controlPoints[index1];
        // Calculate tangent for p0 and p1
        const glm::vec2 tangent0 = HermiteMesh::calculateTangent(controlPoints, index0, true);
        const glm::vec2 tangent1 = HermiteMesh::calculateTangent(controlPoints, index1, false);
        // Interpolate the curve between control points p0 and p1
        for (uint32_t j = 0; j <= steps; ++j) {
            const uint32_t currentIndex = index0 * steps + j;
            const float t = static_cast<float>(j) / steps;
            // Hermite basis functions
            const float phi0 = 2 * t * t * t - 3 * t * t + 1;
            const float phi1 = t * t * t - 2 * t * t + t;
            const float psi0 = -2 * t * t * t + 3 * t * t;
            const float psi1 = t * t * t - t * t;
            // Calculate the position of the vertex on the Hermite curve
            const float x = p0.vert.position.x * phi0 + tangent0.x * phi1 + p1.vert.position.x * psi0 + tangent1.x * psi1;
            const float y = p0.vert.position.y * phi0 + tangent0.y * phi1 + p1.vert.position.y * psi0 + tangent1.y * psi1;
            // Add the new vertex to the result
            vertices[currentIndex + filled] = Vertex{ glm::vec2(x, y), j < steps / 2 ? controlPoints[index0].vert.color : controlPoints[index1].vert.color };
        }
    }
    return vertices;
}

std::vector<uint32_t> HermiteMesh::generateHermiteIndices(const uint32_t vertexCount, const bool filled) {
	std::vector<uint32_t> indices;
    for (uint32_t i = 0; i < vertexCount; ++i) {
        indices.emplace_back(i);
    }
	return indices;
}