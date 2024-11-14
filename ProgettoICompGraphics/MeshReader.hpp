#pragma once

#include <string>

#include "Mesh.hpp"
#include "HermiteMesh.hpp"

namespace MeshReader {
    Mesh loadBasicMesh(const std::string& filename, const uint32_t renderType);
    HermiteMesh loadHermiteMesh(const std::string& filename, const uint32_t resolutionSteps, const bool filled);
};