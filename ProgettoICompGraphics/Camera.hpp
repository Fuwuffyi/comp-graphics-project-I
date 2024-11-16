#pragma once

#include <glm/glm.hpp>

/**
 * Class that rapresents a 2D camera.
 */
class Camera {
private:
	glm::vec2 position;
	float invAspectRatio;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 cameraMatrix;

	/**
	 * Updates the camera's view matrix.
	 * 
	 */
	void updateViewMatrix();

	/**
	 * Updates the camera's projection matrix.
	 * 
	 */
	void updateProjectionMatrix();
public:
	/**
	 * Creates a new camera at the given position.
	 * 
	 * \param _position The camera's position.
	 * \param invAspectRatio The camera's height/width aspect ratio.
	 */
	Camera(const glm::vec2& _position, const float invAspectRatio);

	/**
	 * Updates the camera's combined matrix.
	 * 
	 */
	void updateCameraMatrix();

	/**
	 * Getter for the camera's position.
	 * 
	 * \return The camera's current position.
	 */
	const glm::vec2& getPosition() const;

	/**
	 * Setter for the camera's position.
	 * 
	 * \param _position The new camera's position
	 */
	void setPosition(const glm::vec2& _position);

	/**
	 * Changes the camera's position by an offset.
	 * 
	 * \param offset The offset to change the camera's position by.
	 */
	void changePosition(const glm::vec2& offset);

	/**
	 * Getter for the camera's inverse aspect ratio.
	 * 
	 * \return The camera's inverse aspect ratio.
	 */
	float getInvAspectRatio() const;

	/**
	 * Setter for the camera's inverse aspect ratio.
	 * 
	 * \param _invAspectRatio The new aspect ratio of the camera.
	 */
	void changeAspectRatio(const float _invAspectRatio);

	/**
	 * Getter for the camera's view matrix.
	 * 
	 * \return The camera's view matrix.
	 */
	const glm::mat4& getViewMatrix() const;

	/**
	 * Getter for the camera's projection matrix.
	 *
	 * \return The camera's projection matrix.
	 */
	const glm::mat4& getProjectionMatrix() const;

	/**
	 * Getter for the camera's combined matrix.
	 *
	 * \return The camera's combined matrix.
	 */
	const glm::mat4& getCameraMatrix() const;
};