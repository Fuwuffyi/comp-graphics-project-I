#pragma once

#include <glm/glm.hpp>

/**
 * Forward declaration for the Camera class.
 */
class Camera;

/**
 * Forward declaration for the Shader class.
 */
class Shader;

/**
 * Forward declaration for the Mesh class.
 */
class Mesh;

/**
 * Forward declaration for the BoundingBox class.
 */
class BoundingBox;

/**
 * Class rapresenting a game object with position, rotation and a scale.
 */
class GameObject {
protected:
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

	glm::mat4 matTranslation;
	glm::mat4 matRotation;
	glm::mat4 matScale;
	glm::mat4 matObj;

	/**
	 * Updates the translation matrix of the object.
	 * 
	 */
	void updateTranslationMatrix();

	/**
	 * Updates the rotation matrix of the object.
	 *
	 */
	void updateRotationMatrix();

	/**
	 * Updates the scale matrix of the object.
	 *
	 */
	void updateScaleMatrix();

	/**
	 * Updates the object's combined matrix
	 *
	 */
	void updateObjectMatrix();
public:
	const Mesh* mesh;
	const Shader* shader;

	/**
	 * Constructs a GameObject.
	 *
	 * \param _mesh The mesh to draw the object with.
	 * \param _shader The shader to draw the object with.
	 * \param pos The position of the object.
	 */
	GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos);

	/**
	 * Constructs a GameObject.
	 *
	 * \param _mesh The mesh to draw the object with.
	 * \param _shader The shader to draw the object with.
	 * \param pos The position of the object.
	 * \param _scale The scale of the object.
	 */
	GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const glm::vec2& _scale);

	/**
	 * Constructs a GameObject.
	 *
	 * \param _mesh The mesh to draw the object with.
	 * \param _shader The shader to draw the object with.
	 * \param pos The position of the object.
	 * \param rot The rotation of the object in degrees.
	 */
	GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot);

	/**
	 * Constructs a GameObject.
	 * 
	 * \param _mesh The mesh to draw the object with.
	 * \param _shader The shader to draw the object with.
	 * \param pos The position of the object.
	 * \param rot The rotation of the object in degrees.
	 * \param _scale The scale of the object.
	 */
	GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale);

	/**
	 * Getter for the object's position.
	 * 
	 * \return The object's position.
	 */
	const glm::vec2& getPosition() const;

	/**
	 * Getter for the object's rotation.
	 *
	 * \return The object's rotation.
	 */
	const float getRotation() const;

	/**
	 * Getter for the object's scale.
	 *
	 * \return The object's scale.
	 */
	const glm::vec2& getScale() const;

	/**
	 * Getter for the object's translation matrix.
	 *
	 * \return The object's translation matrix.
	 */
	const glm::mat4& getTranslationMatrix() const;

	/**
	 * Getter for the object's rotation matrix.
	 *
	 * \return The object's rotation matrix.
	 */
	const glm::mat4& getRotationMatrix() const;

	/**
	 * Getter for the object's scale matrix.
	 *
	 * \return The object's scale matrix.
	 */
	const glm::mat4& getScaleMatrix() const;

	/**
	 * Getter for the object's combined matrix.
	 *
	 * \return The object's combined matrix.
	 */
	const glm::mat4& getObjectMatrix() const;

	/**
	 * Sets the object's position.
	 * 
	 * \param pos The new object's position.
	 */
	void setPosition(const glm::vec2& pos);

	/**
	 * Changes the object's position by an offset.
	 * 
	 * \param offset The offset to change the position by.
	 */
	void changePosition(const glm::vec2& offset);

	/**
	 * Sets the object's rotation.
	 *
	 * \param pos The new object's rotation.
	 */
	void setRotation(const float rot);

	/**
	 * Changes the object's rotation by an offset.
	 *
	 * \param offset The offset to change the rotation by.
	 */
	void changeRotation(const float offset);

	/**
	 * Sets the object's scale.
	 *
	 * \param pos The new object's scale.
	 */
	void setScale(const glm::vec2& scale);

	/**
	 * Changes the object's scale by an offset.
	 *
	 * \param offset The offset to change the scale by.
	 */
	void changeScale(const glm::vec2& offset);

	/**
	 * Getter for the object's translated bounding box.
	 * 
	 * \return A bounding box with already applied the object's transformation.
	 */
	BoundingBox getBoundingBox() const;

	/**
	 * Method to draw the game object.
	 * 
	 * \param cam The camera to draw the object from.
	 */
	virtual void draw(const Camera& cam) const;
};