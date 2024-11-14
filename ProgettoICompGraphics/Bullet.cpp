#include "Bullet.hpp"

Bullet::Bullet(const Mesh* _mesh, const Shader* _shader, const glm::vec2& _position, const float& _rotation, const glm::vec2& startingVelocity)
:
	PhysicsGameObject(_mesh, _shader, _position, _rotation, glm::vec2(0.0075f), 1.0f, startingVelocity, 0.0f, 2.0f, 0.0f, 1.0f, 0.0f),
	shouldDelete(false),
	timer(0.0f)
{}

void Bullet::update(const float deltaTime) {
	this->tickPhysics(deltaTime);
	timer += deltaTime;
	// After 10 seconds mark for deletion
	if (timer > 5.0f) {
		this->shouldDelete = true;
	}
}

bool Bullet::getShouldDelete() const {
	return this->shouldDelete;
}