#include "LevelManager.hpp"

#include "GameSettings.hpp"

#include "Asteroid.hpp"

std::vector<Asteroid> LevelManager::generateLevel(const Mesh* asteroidMesh, const Shader* asteroidShader, const glm::vec2& safePosition, const uint16_t level) {
	const uint32_t asteroidCount = level + 2;
	std::vector<Asteroid> asteroids;
	for (uint32_t i = 0; i < asteroidCount; ++i) {
		asteroids.emplace_back(asteroidMesh, asteroidShader, glm::vec2(GameSettings::ASTEROID_MAX_SCALE));
		// If the asteroid is too close, regenerate it
		while (glm::length(asteroids[i].getPosition() - safePosition) < GameSettings::ASTEROID_MAX_SCALE * GameSettings::WORLD_SIZE * 1.1f) {
			asteroids[i].randomizePosition();
		}
	}
	return asteroids;
}