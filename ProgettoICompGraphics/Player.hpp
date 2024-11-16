#pragma once

#include "PhysicsGameObject.hpp"
#include "IUpdatableObject.hpp"

class Player : public PhysicsGameObject, IUpdatableObject {
private:
	bool dead;
public:
	Player(const Mesh* _mesh, const Shader* _shader);

	bool isAlive() const;
	void setDead(const bool _dead);

	void update(const float deltaTime) override;
	void draw(const Camera& cam) const override;
};