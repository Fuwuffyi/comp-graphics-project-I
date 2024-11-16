#pragma once

#include "PhysicsGameObject.hpp"
#include "IUpdatableObject.hpp"
/**
 * Class containing an asteroid's information.
 */
class Asteroid : public PhysicsGameObject, IUpdatableObject {
private:
	uint32_t uuid; // The id to randomly generate the geometry with
public:
	/**
	 * Constructs an asteroid with a given starting position.
	 * 
	 * \param _mesh The mesh to draw the asteroid with.
	 * \param _shader The shader to draw the asteroid with.
	 * \param startPos The starting position of the asteroid.
	 * \param startScale The starting scale of the asteroid.
	 */
	Asteroid(const Mesh* _mesh, const Shader* _shader, const glm::vec2& startPos, const glm::vec2& startScale);

	/**
	 * Constructs an asteroid randomly in space.
	 *
	 * \param _mesh The mesh to draw the asteroid with.
	 * \param _shader The shader to draw the asteroid with.
	 * \param startScale The starting scale of the asteroid.
	 */
	Asteroid(const Mesh* _mesh, const Shader* _shader, const glm::vec2& startScale);

	/**
	 * Randomizes the current position of the asteroid to generate randomly.
	 * 
	 */
	void randomizePosition();

	/**
	 * Updates the asteroid's position and rotation over time.
	 * 
	 * \param deltaTime The time between this frame and last frame.
	 */
	void update(const float deltaTime) override;

	/**
	 * Function to draw the asteroid.
	 * 
	 * \param cam The camera to draw the asteroid from.
	 */
	void draw(const Camera& cam) const override;
};