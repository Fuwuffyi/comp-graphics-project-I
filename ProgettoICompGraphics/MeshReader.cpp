#include "MeshReader.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <iostream>

namespace MeshReader{
    Mesh loadBasicMesh(const std::string& filename, const uint32_t renderType) {
        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open mesh file");
        }
        std::string line;
        while (std::getline(file, line)) {
            std::istringstream ss(line);
            char type;
            ss >> type;
            if (type == 'v') {
                Vertex vertex;
                ss >> vertex.position.x >> vertex.position.y >> vertex.color.r >> vertex.color.g >> vertex.color.b >> vertex.color.a;
                vertices.push_back(vertex);
            }
            else if (type == 'i') {
                uint32_t index;
                ss >> index;
                indices.push_back(index);
            }
        }
        file.close();
        return Mesh(vertices, indices, renderType);
    }
};