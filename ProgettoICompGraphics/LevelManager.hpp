#pragma once

#include <vector>
#include <cstdint>
#include <glm/glm.hpp>

/**
 * Forward declaration for the Mesh class.
 */
class Mesh;

/**
 * Forward declaration for the Shader class.
 */
class Shader;

/**
 * Forward declaration for the Asteroid class.
 */
class Asteroid;

/**
 * A simple namespace holding functions and information to generate a new level.
 */
namespace LevelManager {
	/**
	 * Generates asteroids based on a given level
	 *
	 * \param asteroidMesh The mesh for the generated asteroid.
	 * \param asteroidShader The shader for the generated asteroid.
	 * \param safePosition The player's position, to not generate asteroids there.
	 * \param level The current level to generate asteroids from.
	 * \return A vector containing level + 2 asteroids.
	 */
	std::vector<Asteroid> generateLevel(const Mesh* asteroidMesh, const Shader* asteroidShader, const glm::vec2& safePosition, const uint16_t level);
};