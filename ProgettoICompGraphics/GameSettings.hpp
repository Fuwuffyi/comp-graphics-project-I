#pragma once

/**
 * Namespace that holds some important values for the game.
 */
namespace GameSettings {
	constexpr float ASTEROID_MAX_SCALE = 0.3f;
	constexpr float ASTEROID_MIN_SCALE = 0.0375f;
	constexpr float ASTEROID_MAX_SCORE = 100.0f;
	constexpr float ASTEROID_MAX_SPEED = 0.6f;

	constexpr float BULLET_DESPAWN_TIMER = 3.0f;
	constexpr float BULLET_MAX_SPEED = 2.0f;

	constexpr float PLAYER_MAX_SPEED = 1.0f;
	constexpr float PLAYER_MAX_ROT_SPEED = 180.0f;
	constexpr float PLAYER_FRIC = 0.9f;
	constexpr float PLAYER_ROT_FRIC = 0.02f;

	constexpr float WORLD_SIZE = 3.0f;
};