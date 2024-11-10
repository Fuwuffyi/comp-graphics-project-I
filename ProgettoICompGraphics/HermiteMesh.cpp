#include "HermiteMesh.hpp"

#include <glad/glad.h>

#include <iostream>

HermiteMesh::HermiteMesh(const std::vector<HermiteVertex>& controlPoints, const uint32_t steps)
:
    Mesh(
        HermiteMesh::calculateHermiteVertices(controlPoints, steps),
        HermiteMesh::generateHermiteIndices((controlPoints.size() - 1) * steps),
        GL_LINE_LOOP
    )
{}

static glm::vec2 calculateTangent(const std::vector<HermiteVertex>& controlPoints, size_t index, bool isStart) {
    const HermiteVertex& point = controlPoints[index];
    // Calculate the tangent based on the control point's tension, bias, and continuity
    glm::vec2 tangent;
    if (isStart) {
        // Start tangent calculation (i.e., for the first control point)
        if (index == 0) {
            tangent.x = (controlPoints[1].vert.position.x - point.vert.position.x) * 0.5f;
            tangent.y = (controlPoints[1].vert.position.y - point.vert.position.y) * 0.5f;
        } else {
            const HermiteVertex& prevPoint = controlPoints[index - 1];
            tangent.x = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (point.vert.position.x - prevPoint.vert.position.x) * 0.5f;
            tangent.y = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (point.vert.position.y - prevPoint.vert.position.y) * 0.5f;
        }
    }
    else {
        // End tangent calculation (i.e., for the last control point)
        if (index == controlPoints.size() - 1) {
            tangent.x = (point.vert.position.x - controlPoints[index - 1].vert.position.x) * 0.5f;
            tangent.y = (point.vert.position.y - controlPoints[index - 1].vert.position.y) * 0.5f;
        } else {
            const HermiteVertex& nextPoint = controlPoints[index + 1];
            tangent.x = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (nextPoint.vert.position.x - point.vert.position.x) * 0.5f;
            tangent.y = (1 - point.tension) * (1 - point.bias) * (1 - point.continuity) * (nextPoint.vert.position.y - point.vert.position.y) * 0.5f;
        }
    }
    return tangent;
}

std::vector<Vertex> HermiteMesh::calculateHermiteVertices(const std::vector<HermiteVertex>& controlPoints, const uint32_t steps) {
    std::vector<Vertex> vertices;
    // Iterate through control points in pairs
    for (uint32_t i = 0; i < controlPoints.size() - 1; ++i) {
        const HermiteVertex& p0 = controlPoints[i];
        const HermiteVertex& p1 = controlPoints[i + 1];
        // Calculate tangent for p0 and p1
        const glm::vec2 tangent0 = calculateTangent(controlPoints, i, true);
        const glm::vec2 tangent1 = calculateTangent(controlPoints, i + 1, false);
        // Interpolate the curve between control points p0 and p1
        for (uint32_t j = 0; j <= steps; ++j) {
            float t = static_cast<float>(j) / steps;
            // Hermite basis functions
            float phi0 = 2 * t * t * t - 3 * t * t + 1;
            float phi1 = t * t * t - 2 * t * t + t;
            float psi0 = -2 * t * t * t + 3 * t * t;
            float psi1 = t * t * t - t * t;
            // Calculate the position of the vertex on the Hermite curve
            float x = p0.vert.position.x * phi0 + tangent0.x * phi1 + p1.vert.position.x * psi0 + tangent1.x * psi1;
            float y = p0.vert.position.y * phi0 + tangent0.y * phi1 + p1.vert.position.y * psi0 + tangent1.y * psi1;
            // Add the new vertex to the result
            vertices.emplace_back(Vertex { glm::vec2(x, y), controlPoints[i].vert.color });
        }
    }
    return vertices;
}

std::vector<uint32_t> HermiteMesh::generateHermiteIndices(const uint32_t vertexCount) {
	std::vector<uint32_t> indices;
    for (uint32_t i = 0; i < vertexCount; ++i) {
        indices.emplace_back(i);
    }
	return indices;
}