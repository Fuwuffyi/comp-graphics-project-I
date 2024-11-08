#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "Mesh.hpp"
#include "Shader.hpp"

class GameObject {
private:
	glm::vec2 position;
	float rotation;
	glm::vec2 scale;

public:
	const std::shared_ptr<Mesh> mesh;
	const std::shared_ptr<Shader> shader;

	GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos);
	GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const glm::vec2& _scale);
	GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const float rot);
	GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale);

	void draw(const Camera& cam) const;

};