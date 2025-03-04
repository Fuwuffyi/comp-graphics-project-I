#include "MeshReader.hpp"

#include "Mesh.hpp"
#include "HermiteMesh.hpp"

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

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
            // If the line starts with "v" it is a vertex declaration
            if (type == 'v') {
                Vertex vertex;
                ss >> vertex.position.x >> vertex.position.y >> 
                    vertex.color.r >> vertex.color.g >> vertex.color.b >> vertex.color.a;
                vertices.push_back(vertex);
            }
            // If the line starts with "i" it is a index declaration
            else if (type == 'i') {
                uint32_t index;
                ss >> index;
                indices.push_back(index);
            }
        }
        file.close();
        return Mesh(vertices, indices, renderType);
    }

    HermiteMesh loadHermiteMesh(const std::string& filename, const uint32_t resolutionSteps, const bool filled) {
        std::vector<HermiteControlPoint> controlPoints;
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
                HermiteControlPoint cp;
                ss >> cp.vert.position.x >> cp.vert.position.y >> 
                    cp.vert.color.r >> cp.vert.color.g >> cp.vert.color.b >> cp.vert.color.a >> 
                    cp.tension >> cp.bias >> cp.continuity;
                controlPoints.push_back(cp);
            }
        }
        file.close();
        return HermiteMesh(controlPoints, resolutionSteps, filled);
    }
};