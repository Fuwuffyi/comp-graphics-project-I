#pragma once

#include "PhysicsGameObject.hpp"
#include "IUpdatableObject.hpp"

// Asteroid scale goes from: 3.0f

class Asteroid : public PhysicsGameObject, IUpdatableObject {
public:
	static constexpr float MAX_SCALE = 0.3f;
	static constexpr float MIN_SCALE = 0.0375f;
	static constexpr float MAX_SCORE = 100.0f;
public:
	Asteroid(const Mesh* _mesh, const Shader* _shader, const glm::vec2& startPos, const glm::vec2& startScale, const glm::vec2& startAccel);

	void update(const float deltaTime) override;
};