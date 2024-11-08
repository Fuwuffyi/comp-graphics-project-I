#include "GameObject.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/gtc/type_ptr.hpp>

GameObject::GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos)
:
	GameObject(_mesh, _shader, pos, 0.0f, glm::vec2(1.0f))
{}

GameObject::GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const glm::vec2& _scale)
:
	GameObject(_mesh, _shader, pos, 0.0f, _scale)
{}

GameObject::GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const float rot)
:
	GameObject(_mesh, _shader, pos, rot, glm::vec2(1.0f))
{}

GameObject::GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale)
:
	position(pos),
	rotation(rot),
	scale(_scale),
	mesh(_mesh),
	shader(_shader)
{}

void GameObject::draw(const Camera& cam) const {
	this->shader->activate();
	glUniformMatrix4fv(this->shader->getUniformLocation("camMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getCameraMatrix()));
	mesh->draw();
}