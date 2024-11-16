#pragma once

/**
 * A simple interface for more complex objects that update with time.
 */
class IUpdatableObject {
public:
	/**
	 * Method to update the object.
	 * 
	 * \param deltaTime The time between this and the last frame.
	 */
	virtual void update(const float deltaTime) = 0;
};