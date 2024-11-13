#pragma once

#include "PhysicsGameObject.hpp"
#include "IUpdatableObject.hpp"

class Player : public PhysicsGameObject, IUpdatableObject {
public:
	Player(const Mesh* _mesh, const Shader* _shader);

	void update(const float deltaTime) override;
};