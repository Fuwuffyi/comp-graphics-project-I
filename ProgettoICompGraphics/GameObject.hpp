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

	glm::mat4 matTranslation;
	glm::mat4 matRotation;
	glm::mat4 matScale;
	glm::mat4 matObj;

	void updateTranslationMatrix();
	void updateRotationMatrix();
	void updateScaleMatrix();

	void updateObjectMatrix();

public:
	const std::shared_ptr<Mesh> mesh;
	const std::shared_ptr<Shader> shader;

	GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos);
	GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const glm::vec2& _scale);
	GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const float rot);
	GameObject(const std::shared_ptr<Mesh>& _mesh, const std::shared_ptr<Shader> _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale);

	const glm::vec2& getPostion() const;
	const float getRotation() const;
	const glm::vec2& getScale() const;

	void setPosition(const glm::vec2& pos);
	void changePosition(const glm::vec2& offset);

	void setRotation(const float rot);
	void changeRotation(const float offset);

	void setScale(const glm::vec2& scale);
	void changeScale(const glm::vec2& offset);

	void draw(const Camera& cam);
};