#pragma once

#include <vector>
#include <cstdint>

class Mesh;
class Shader;
class Player;
class Asteroid;

namespace LevelManager {
	std::vector<Asteroid> generateLevel(const Mesh* asteroidMesh, const Shader* asteroidShader, const Player& player, const uint16_t level);
};