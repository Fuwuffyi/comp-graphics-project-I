#include "Player.hpp"

#include "Keyboard.hpp"

Player::Player(const Mesh* _mesh, const Shader* _shader) 
:
	PhysicsGameObject(_mesh, _shader, glm::vec2(0.0f), 0.0f, glm::vec2(0.05f), 15.0f, glm::vec2(0.0f), 0.0f, 1.0f, 180.0f, 0.9f, 0.02f)
{}

void Player::update(const float deltaTime) {
	if (Keyboard::key(GLFW_KEY_A)) {
		this->applyRotationalForce(45.0f);
	}
	if (Keyboard::key(GLFW_KEY_D)) {
		this->applyRotationalForce(-45.0f);
	}
	if (Keyboard::key(GLFW_KEY_W)) {
		this->applyForce(this->getHeadingVec() * 0.1f);
	}
	if (Keyboard::key(GLFW_KEY_S)) {
		this->applyForce(this->getHeadingVec() * -0.1f);
	}
	this->tickPhysics(deltaTime);
}