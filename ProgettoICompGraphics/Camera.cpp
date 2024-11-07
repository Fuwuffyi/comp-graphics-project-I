#include "Camera.hpp"

#include <math.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(const glm::vec2& _position)
	:
	position(_position),
	viewMatrix(1.0f),
	projectionMatrix(glm::ortho(0.0f, 1.0f, 0.0f, 1.0f)),
	cameraMatrix(1.0f)
{
	this->updateViewMatrix();
	this->updateCameraMatrix();
}

void Camera::updateViewMatrix() {
	this->viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-this->position, 0.0f));
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

const glm::mat4& Camera::getViewMatrix() const {
	return this->viewMatrix;
}

const glm::mat4& Camera::getProjectionMatrix() const {
	return this->projectionMatrix;
}

const glm::mat4& Camera::getCameraMatrix() const {
	return this->cameraMatrix;
}
