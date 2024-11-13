#include "PhysicsGameObject.hpp"


PhysicsGameObject::PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric)
:
	GameObject(_mesh, _shader, pos),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass),
	maxSpeed(_maxSpeed),
	maxRotSpeed(_maxRotSpeed),
	fric(_fric),
	rotFric(_rotFric)
{}

PhysicsGameObject::PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const glm::vec2& _scale, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric)
:
	GameObject(_mesh, _shader, pos, _scale),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass),
	maxSpeed(_maxSpeed),
	maxRotSpeed(_maxRotSpeed),
	fric(_fric),
	rotFric(_rotFric)
{}

PhysicsGameObject::PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric)
:
	GameObject(_mesh, _shader, pos, rot),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass),
	maxSpeed(_maxSpeed),
	maxRotSpeed(_maxRotSpeed),
	fric(_fric),
	rotFric(_rotFric)
{}

PhysicsGameObject::PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric)
:
	GameObject(_mesh, _shader, pos, rot, _scale),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass),
	maxSpeed(_maxSpeed),
	maxRotSpeed(_maxRotSpeed),
	fric(_fric),
	rotFric(_rotFric)
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
	const glm::vec4 rotationDir = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * this->getRotationMatrix();
	return glm::vec2(rotationDir.x, -rotationDir.y);
}

void PhysicsGameObject::update(const float deltaTime) {
	this->changePosition(this->acceleration * deltaTime);
	this->acceleration *= 1 - (1 - this->fric) * deltaTime;
	this->changeRotation(this->rotationalAcceleration * deltaTime);
	this->rotationalAcceleration *= 1 - (1 - this->rotFric) * deltaTime;
}