#pragma once

#include "PhysicsGameObject.hpp"
#include "IUpdatableObject.hpp"

class Asteroid : public PhysicsGameObject, IUpdatableObject {
private:
	uint32_t uuid;
public:
	Asteroid(const Mesh* _mesh, const Shader* _shader, const glm::vec2& startPos, const glm::vec2& startScale);
	Asteroid(const Mesh* _mesh, const Shader* _shader, const glm::vec2& startScale);

	void update(const float deltaTime) override;
	void draw(const Camera& cam) const override;
};