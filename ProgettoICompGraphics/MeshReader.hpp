#pragma once

#include <string>

#include "Mesh.hpp"

namespace MeshReader {
    Mesh loadBasicMesh(const std::string& filename, const uint32_t renderType);
};