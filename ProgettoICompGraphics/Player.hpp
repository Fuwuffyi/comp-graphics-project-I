#pragma once

#include "PhysicsGameObject.hpp"
#include "IUpdatableObject.hpp"

/**
 * Class containing the player's information.
 */
class Player : public PhysicsGameObject, IUpdatableObject {
private:
	bool dead; // True if the player has died
public:
	/**
	 * Constructor for the player object.
	 * 
	 * \param _mesh The mesh the player will be rapresented by.
	 * \param _shader The shader to draw the player with.
	 */
	Player(const Mesh* _mesh, const Shader* _shader);

	/**
	 * Getter for the player's dead property.
	 * 
	 * \return True if the player is still alive.
	 */
	bool isAlive() const;

	/**
	 * Setter for the player's dead property.
	 * 
	 * \param _dead The new player's dead state.
	 */
	void setDead(const bool _dead);

	/**
	 * Update the player's object.
	 * 
	 * \param deltaTime The time between this frame and the last frame.
	 */
	void update(const float deltaTime) override;

	/**
	 * Method to draw the player on screen.
	 * 
	 * \param cam The camera to draw the player from.
	 */
	void draw(const Camera& cam) const override;
};