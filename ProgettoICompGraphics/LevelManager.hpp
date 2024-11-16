#pragma once

#include <vector>
#include <cstdint>

/**
 * Forward declaration for the Mesh class.
 */
class Mesh;

/**
 * Forward declaration for the Shader class.
 */
class Shader;

/**
 * Forward declaration for the Player class.
 */
class Player;

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
	 * \param player The player's pointer, used to not generate asteroids where the player is.
	 * \param level The current level to generate asteroids from.
	 * \return A vector containing level + 3 asteroids.
	 */
	std::vector<Asteroid> generateLevel(const Mesh* asteroidMesh, const Shader* asteroidShader, const Player& player, const uint16_t level);
};