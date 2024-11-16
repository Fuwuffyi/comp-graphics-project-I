#pragma once

#include "GameObject.hpp"

/**
 * Class containing a game object that you can apply forces to.
 */
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
	/**
	 * Constructor for a physics game object.
	 *
	 * \param _mesh The mesh of the object.
	 * \param _shader The shader to draw the object with.
	 * \param pos The starting position of the object.
	 * \param _mass The mass of the object.
	 * \param startAccel The starting acceleration of the object.
	 * \param startRotAccel The starting rotational acceleration of the object.
	 * \param _maxSpeed The maximum speed of the object.
	 * \param _maxRotSpeed The maximum rotational speed of the object.
	 * \param _fric The friction applied to the object's movement.
	 * \param _rotFric The friction applied to the object's rotation.
	 */
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric);
	
	/**
	 * Constructor for a physics game object.
	 *
	 * \param _mesh The mesh of the object.
	 * \param _shader The shader to draw the object with.
	 * \param pos The starting position of the object.
	 * \param _scale The starting scale of the object.
	 * \param _mass The mass of the object.
	 * \param startAccel The starting acceleration of the object.
	 * \param startRotAccel The starting rotational acceleration of the object.
	 * \param _maxSpeed The maximum speed of the object.
	 * \param _maxRotSpeed The maximum rotational speed of the object.
	 * \param _fric The friction applied to the object's movement.
	 * \param _rotFric The friction applied to the object's rotation.
	 */
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const glm::vec2& _scale, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric);
	
	/**
	 * Constructor for a physics game object.
	 *
	 * \param _mesh The mesh of the object.
	 * \param _shader The shader to draw the object with.
	 * \param pos The starting position of the object.
	 * \param rot The starting rotation of the object.
	 * \param _mass The mass of the object.
	 * \param startAccel The starting acceleration of the object.
	 * \param startRotAccel The starting rotational acceleration of the object.
	 * \param _maxSpeed The maximum speed of the object.
	 * \param _maxRotSpeed The maximum rotational speed of the object.
	 * \param _fric The friction applied to the object's movement.
	 * \param _rotFric The friction applied to the object's rotation.
	 */
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric);
	
	/**
	 * Constructor for a physics game object.
	 * 
	 * \param _mesh The mesh of the object.
	 * \param _shader The shader to draw the object with.
	 * \param pos The starting position of the object.
	 * \param rot The starting rotation of the object.
	 * \param _scale The starting scale of the object.
	 * \param _mass The mass of the object.
	 * \param startAccel The starting acceleration of the object.
	 * \param startRotAccel The starting rotational acceleration of the object.
	 * \param _maxSpeed The maximum speed of the object.
	 * \param _maxRotSpeed The maximum rotational speed of the object.
	 * \param _fric The friction applied to the object's movement.
	 * \param _rotFric The friction applied to the object's rotation.
	 */
	PhysicsGameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale, const float _mass, const glm::vec2& startAccel, const float startRotAccel, const float _maxSpeed, const float _maxRotSpeed, const float _fric, const float _rotFric);

	/**
	 * Sets the object's acceleration.
	 * 
	 * \param newAccel The acceleration to set the object's accel to.
	 */
	void setAcceleration(const glm::vec2& newAccel);

	/**
	 * Applies a translational force to the object.
	 * 
	 * \param force The force to apply to the object.
	 */
	void applyForce(const glm::vec2& force);

	/**
	 * Sets the object's rotational acceleration.
	 *
	 * \param newAccel The rotational acceleration to set the object's accel to.
	 */
	void setRotationalAcceleration(const float newRotAccel);

	/**
	 * Applies a rotational force to the object.
	 *
	 * \param force The force to apply to the object.
	 */
	void applyRotationalForce(const float force);

	/**
	 * Getter for the vector of the object's pointing direction.
	 * 
	 * \return The object's pointing direction.
	 */
	glm::vec2 getHeadingVec() const;

	/**
	 * Ticks the object's physics simulation.
	 * 
	 * \param deltaTime The time between this and last frame.
	 */
	void tickPhysics(const float deltaTime);
};