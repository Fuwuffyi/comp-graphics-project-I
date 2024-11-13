#pragma once

// Interface for objects that can update with time.
class IUpdatableObject {
public:
	// Update method for the object
	virtual void update(const float deltaTime) = 0;
};