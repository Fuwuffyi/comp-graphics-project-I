#pragma once

#include "GameObject.hpp"

class PhysicsGameObject {
private:
	GameObject* gameObject;

	glm::vec2 acceleration;
	float rotationalAcceleration;
public:
	const float mass;

	const float maxSpeed;
	const float maxRotSpeed;
public:
	PhysicsGameObject(GameObject* _gameObject, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed);

	void setAcceleration(const glm::vec2& newAccel);
	void applyForce(const glm::vec2& force);

	void setRotationalAcceleration(const float newRotAccel);
	void applyRotationalForce(const float force);

	glm::vec2 getHeadingVec() const;

	void update(const float deltaTime);
};