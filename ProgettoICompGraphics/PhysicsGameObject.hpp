#pragma once

#include "GameObject.hpp"

class PhysicsGameObject : public GameObject {
private:
	glm::vec2 acceleration;
	float rotationalAcceleration;
	float mass;

	float maxSpeed;
	float maxRotSpeed;
	float fric;
	float rotFric;
public:
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric);
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const glm::vec2& _scale, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric);
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric);
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric);

	void setAcceleration(const glm::vec2& newAccel);
	void applyForce(const glm::vec2& force);

	void setRotationalAcceleration(const float newRotAccel);
	void applyRotationalForce(const float force);

	glm::vec2 getHeadingVec() const;

	void tickPhysics(const float deltaTime);
};