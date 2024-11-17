#include "LevelManager.hpp"

#include "GameSettings.hpp"

#include "Player.hpp"
#include "Shader.hpp"
#include "Asteroid.hpp"
#include "BoundingBox.hpp"

std::vector<Asteroid> LevelManager::generateLevel(const Mesh* asteroidMesh, const Shader* asteroidShader, const Player& player, const uint16_t level) {
	const uint32_t asteroidCount = level + 2;
	std::vector<Asteroid> asteroids;
	for (uint32_t i = 0; i < asteroidCount; ++i) {
		asteroids.emplace_back(asteroidMesh, asteroidShader, glm::vec2(GameSettings::ASTEROID_MAX_SCALE));
		while (asteroids[i].getBoundingBox().checkCollisions(player.getBoundingBox())) {
			asteroids[i].randomizePosition();
		}
	}
	return asteroids;
}