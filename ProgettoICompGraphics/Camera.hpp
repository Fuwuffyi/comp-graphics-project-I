#pragma once

#include <glm/glm.hpp>

class Camera {
private:
	glm::vec2 position;
	float invAspectRatio;

	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	glm::mat4 cameraMatrix;

	void updateViewMatrix();
	void updateProjectionMatrix();
public:
	Camera(const glm::vec2& _position, const float invAspectRatio);

	void updateCameraMatrix();

	const glm::vec2& getPosition() const;

	void setPosition(const glm::vec2& _position);
	void changePosition(const glm::vec2& offset);

	void changeAspectRatio(const float _invAspectRatio);

	const glm::mat4& getViewMatrix() const;
	const glm::mat4& getProjectionMatrix() const;
	const glm::mat4& getCameraMatrix() const;
};