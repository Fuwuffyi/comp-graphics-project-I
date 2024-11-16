#pragma once

#include "PhysicsGameObject.hpp"
#include "IUpdatableObject.hpp"

/**
 * Class containing a bullet's information.
 */
class Bullet : public PhysicsGameObject, IUpdatableObject {
private:
	bool shouldDelete; // Flag to check when to delete the bullet
	float timer; // Despawn timer for the bullet
public:
	/**
	 * Constructor for the bullet game object.
	 * 
	 * \param mesh The mesh to draw the bullet with.
	 * \param shader The shader to draw the bullet with.
	 * \param _position The starting position of the bullet.
	 * \param _rotation The starting rotation of the bullet.
	 * \param startingVelocity The starting velocity of the bullet.
	 */
	Bullet(const Mesh* mesh, const Shader* shader, const glm::vec2& _position, const float& _rotation, const glm::vec2& startingVelocity);

	/**
	 * Updates the bullet to move in space.
	 * 
	 * \param deltaTime The time between this frame and last frame.
	 */
	void update(const float deltaTime) override;

	/**
	 * Getter for the bullet's despawn timer.
	 * 
	 * \return True if the bullet should be despawned.
	 */
	bool getShouldDelete() const;
};