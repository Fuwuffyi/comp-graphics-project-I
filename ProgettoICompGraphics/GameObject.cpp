#include "GameObject.hpp"

#include <glad/glad.h>

#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos)
:
	GameObject(_mesh, _shader, pos, 0.0f, glm::vec2(1.0f))
{}

GameObject::GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const glm::vec2& _scale)
:
	GameObject(_mesh, _shader, pos, 0.0f, _scale)
{}

GameObject::GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot)
:
	GameObject(_mesh, _shader, pos, rot, glm::vec2(1.0f))
{}

GameObject::GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale)
:
	position(pos),
	rotation(rot),
	scale(_scale),
	matTranslation(1.0f),
	matRotation(1.0f),
	matScale(1.0f),
	matObj(1.0f),
	mesh(_mesh),
	shader(_shader)
{
	this->updateTranslationMatrix();
	this->updateRotationMatrix();
	this->updateScaleMatrix();
}

const glm::vec2& GameObject::getPosition() const {
	return this->position;
}

const float GameObject::getRotation() const {
	return this->rotation;
}

const glm::vec2& GameObject::getScale() const {
	return this->scale;
}
const glm::mat4& GameObject::getTranslationMatrix() const {
	return this->matTranslation;
}

const glm::mat4& GameObject::getRotationMatrix() const {
	return this->matRotation;
}

const glm::mat4& GameObject::getScaleMatrix() const {
	return this->matScale;
}

const glm::mat4& GameObject::getObjectMatrix() const {
	return this->matObj;
}

void GameObject::setPosition(const glm::vec2& pos) {
	this->position = pos;
	this->updateTranslationMatrix();
}

void GameObject::changePosition(const glm::vec2& offset) {
	this->position += offset;
	this->updateTranslationMatrix();
}

void GameObject::setRotation(const float rot) {
	this->rotation = rot;
	this->updateRotationMatrix();
}

void GameObject::changeRotation(const float offset) {
	this->rotation += offset;
	this->updateRotationMatrix();
}

void GameObject::setScale(const glm::vec2& scale) {
	this->scale = scale;
	this->updateScaleMatrix();
}

void GameObject::changeScale(const glm::vec2& offset) {
	this->scale += offset;
	this->updateScaleMatrix();
}

void GameObject::draw(const Camera& cam) {
	this->updateObjectMatrix();
	this->shader->activate();
	glUniformMatrix4fv(this->shader->getUniformLocation("objMatrix"), 1, GL_FALSE, glm::value_ptr(this->matObj));
	glUniformMatrix4fv(this->shader->getUniformLocation("camMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getCameraMatrix()));
	mesh->draw();
}

void GameObject::updateObjectMatrix() {
	this->matObj = this->matTranslation * this->matRotation * this->matScale;
}

void GameObject::updateTranslationMatrix() {
	this->matTranslation = glm::translate(glm::mat4(1.0f), glm::vec3(this->position, 0.0f));
}

void GameObject::updateRotationMatrix() {
	this->matRotation = glm::rotate(glm::mat4(1.0f), glm::radians(this->rotation), glm::vec3(0.0f, 0.0f, 1.0f));
}

void GameObject::updateScaleMatrix() {
	this->matScale = glm::scale(glm::mat4(1.0f), glm::vec3(this->scale, 1.0f));
}