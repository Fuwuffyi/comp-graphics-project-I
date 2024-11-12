#include "PhysicsGameObject.hpp"

PhysicsGameObject::PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const glm::vec2& pos)
:
	GameObject(_mesh, _shader, pos),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass)
{}
	
PhysicsGameObject::PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const glm::vec2& pos, const glm::vec2& _scale)
:
	GameObject(_mesh, _shader, pos, _scale),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass)
{}

PhysicsGameObject::PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const glm::vec2& pos, const float rot)
:
	GameObject(_mesh, _shader, pos, rot),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass)
{}

PhysicsGameObject::PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const glm::vec2& pos, const float rot, const glm::vec2& _scale)
:
	GameObject(_mesh, _shader, pos, rot, _scale),
	acceleration(startAccel),
	rotationalAcceleration(startRotAccel),
	mass(_mass)
{}

void PhysicsGameObject::setAcceleration(const glm::vec2& newAccel) {
	this->acceleration = newAccel;
}

void PhysicsGameObject::applyForce(const glm::vec2& force) {
	this->acceleration += force / this->mass;
	// Check for max speed (4.0f)
	if (glm::dot(this->acceleration, this->acceleration) > 4.0f) {
		this->acceleration = glm::normalize(this->acceleration) * 2.0f;
	}
}

void PhysicsGameObject::setRotationalAcceleration(const float newRotAccel) {
	this->rotationalAcceleration = newRotAccel;
}

void PhysicsGameObject::applyRotationalForce(const float force) {
	this->rotationalAcceleration += force / this->mass;
	// Check for max rotational speed (4.0f)
	if (this->rotationalAcceleration > 4.0f) {
		this->rotationalAcceleration = 4.0f;
	}
}

glm::vec2 PhysicsGameObject::getHeadingVec() const {
	const glm::vec4 rotationDir = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f) * this->matRotation;
	return glm::vec2(rotationDir.x, -rotationDir.y);
}

void PhysicsGameObject::update() {
	this->changePosition(this->acceleration);
	this->acceleration *= 0.99f;
	this->changeRotation(this->rotationalAcceleration);
	this->rotationalAcceleration *= 0.99f;
}