#include "PhysicsGameObject.hpp"

PhysicsGameObject::PhysicsGameObject(GameObject* _gameObject, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed)
:
	gameObject(_gameObject),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass),
	maxSpeed(_maxSpeed),
	maxRotSpeed(_maxRotSpeed)
{}

void PhysicsGameObject::setAcceleration(const glm::vec2& newAccel) {
	this->acceleration = newAccel;
}

void PhysicsGameObject::applyForce(const glm::vec2& force) {
	this->acceleration += force / this->mass;
	// Check for max speed
	if (glm::dot(this->acceleration, this->acceleration) > maxSpeed * maxSpeed) {
		this->acceleration = glm::normalize(this->acceleration) * maxSpeed;
	}
}

void PhysicsGameObject::setRotationalAcceleration(const float newRotAccel) {
	this->rotationalAcceleration = newRotAccel;
}

void PhysicsGameObject::applyRotationalForce(const float force) {
	this->rotationalAcceleration += force / this->mass;
	// Check for max rotational speed
	this->rotationalAcceleration = glm::clamp(this->rotationalAcceleration, -maxRotSpeed, maxRotSpeed);
}

glm::vec2 PhysicsGameObject::getHeadingVec() const {
	const glm::vec4 rotationDir = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * this->gameObject->getRotationMatrix();
	return glm::vec2(rotationDir.x, -rotationDir.y);
}

void PhysicsGameObject::update(const float deltaTime) {
	this->gameObject->changePosition(this->acceleration * deltaTime);
	this->gameObject->changeRotation(this->rotationalAcceleration * deltaTime);
}