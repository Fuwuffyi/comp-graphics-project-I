#pragma once

#include "PhysicsGameObject.hpp"
#include "IUpdatableObject.hpp"

class Bullet : public PhysicsGameObject, IUpdatableObject {
private:
	bool shouldDelete;
	float timer;
public:
	Bullet(const Mesh* mesh, const Shader* shader, const glm::vec2& _position, const float& _rotation, const glm::vec2& startingVelocity);

	void update(const float deltaTime) override;
	bool getShouldDelete() const;
};