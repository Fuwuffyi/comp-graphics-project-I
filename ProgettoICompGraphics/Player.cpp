#include "Player.hpp"

#include "GameSettings.hpp"
#include "Keyboard.hpp"

Player::Player(const Mesh* _mesh, const Shader* _shader) 
:
	PhysicsGameObject(_mesh, _shader, glm::vec2(0.0f), 0.0f, glm::vec2(0.05f), 15.0f, glm::vec2(0.0f), 0.0f, GameSettings::PLAYER_MAX_SPEED, GameSettings::PLAYER_MAX_ROT_SPEED, GameSettings::PLAYER_FRIC, GameSettings::PLAYER_ROT_FRIC),
	dead(false)
{}

bool Player::isAlive() const {
	return !this->dead;
}

void Player::setDead(const bool _dead) {
	this->dead = _dead;
}

void Player::update(const float deltaTime) {
	if (!this->dead) {
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
		if (glm::length(this->getPosition()) > GameSettings::WORLD_SIZE) {
			this->setPosition(-this->getPosition());
		}
	}
}

void Player::draw(const Camera& cam) const {
	if (!this->dead) {
		PhysicsGameObject::draw(cam);
	}
}