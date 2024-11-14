#pragma once

#include <string>

class Mesh;
class HermiteMesh;

namespace MeshReader {
    Mesh loadBasicMesh(const std::string& filename, const uint32_t renderType);
    HermiteMesh loadHermiteMesh(const std::string& filename, const uint32_t resolutionSteps, const bool filled);
};