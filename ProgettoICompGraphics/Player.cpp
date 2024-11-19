#include "Player.hpp"

#include "GameSettings.hpp"
#include "Keyboard.hpp"

Player::Player(const Mesh* _mesh, const Shader* _shader) 
:
	PhysicsGameObject(_mesh, _shader, glm::vec2(0.0f), 0.0f, glm::vec2(0.05f), 150.0f, glm::vec2(0.0f), 0.0f, GameSettings::PLAYER_MAX_SPEED, GameSettings::PLAYER_MAX_ROT_SPEED, GameSettings::PLAYER_FRIC, GameSettings::PLAYER_ROT_FRIC),
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
		if (Keyboard::key(GLFW_KEY_A) || Keyboard::key(GLFW_KEY_LEFT)) {
			this->applyRotationalForce(45000.0f * deltaTime);
		}
		if (Keyboard::key(GLFW_KEY_D) || Keyboard::key(GLFW_KEY_RIGHT)) {
			this->applyRotationalForce(-45000.0f * deltaTime);
		}
		if (Keyboard::key(GLFW_KEY_W) || Keyboard::key(GLFW_KEY_UP)) {
			this->applyForce(this->getHeadingVec() * 1000.0f * deltaTime);
		}
		if (Keyboard::key(GLFW_KEY_S) || Keyboard::key(GLFW_KEY_DOWN)) {
			this->applyForce(this->getHeadingVec() * -1000.0f * deltaTime);
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