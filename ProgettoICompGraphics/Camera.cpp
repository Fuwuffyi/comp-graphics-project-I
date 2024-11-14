#include "Camera.hpp"

#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec2& _position, const float _invAspectRatio)
	:
	position(_position),
	invAspectRatio(_invAspectRatio),
	viewMatrix(1.0f),
	projectionMatrix(glm::ortho(-invAspectRatio, invAspectRatio, -1.0f, 1.0f)),
	cameraMatrix(1.0f)
{
	this->updateViewMatrix();
	this->updateCameraMatrix();
}

void Camera::updateViewMatrix() {
	this->viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-this->position, 0.0f));
}

void Camera::updateProjectionMatrix() {
	this->projectionMatrix = glm::ortho(-1.0f, 1.0f, -invAspectRatio, invAspectRatio);
}

void Camera::updateCameraMatrix() {
	this->cameraMatrix = this->projectionMatrix * this->viewMatrix;
}

const glm::vec2& Camera::getPosition() const {
	return this->position;
}

void Camera::setPosition(const glm::vec2& _position) {
	this->position = _position;
	this->updateViewMatrix();
}

void Camera::changePosition(const glm::vec2& offset) {
	this->position += offset;
	this->updateViewMatrix();
}

float Camera::getInvAspectRatio() const {
	return this->invAspectRatio;
}

void Camera::changeAspectRatio(const float _invAspectRatio) {
	this->invAspectRatio = _invAspectRatio;
	this->updateProjectionMatrix();
}

const glm::mat4& Camera::getViewMatrix() const {
	return this->viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const {
	return this->projectionMatrix;
}

const glm::mat4& Camera::getCameraMatrix() const {
	return this->cameraMatrix;
}
