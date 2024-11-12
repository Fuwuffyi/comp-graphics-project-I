#pragma once

#include "GameObject.hpp"

class PhysicsGameObject : public GameObject {
private:
	glm::vec2 acceleration;
	float rotationalAcceleration;
public:
	const float mass;
public:

	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const glm::vec2& pos);
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const glm::vec2& pos, const glm::vec2& _scale);
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const glm::vec2& pos, const float rot);
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const glm::vec2& pos, const float rot, const glm::vec2& _scale);

	void setAcceleration(const glm::vec2& newAccel);
	void applyForce(const glm::vec2& force);

	void setRotationalAcceleration(const float newRotAccel);
	void applyRotationalForce(const float force);

	glm::vec2 getHeadingVec() const;

	void update();
};