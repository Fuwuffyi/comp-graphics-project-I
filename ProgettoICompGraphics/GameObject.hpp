#pragma once

#include <glm/glm.hpp>

#include <memory>

#include "Mesh.hpp"
#include "Shader.hpp"

class GameObject {
protected:
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
	const Mesh* mesh;
	const Shader* shader;

	GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos);
	GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const glm::vec2& _scale);
	GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot);
	GameObject(const Mesh* _mesh, const Shader* _shader, const glm::vec2& pos, const float rot, const glm::vec2& _scale);

	const glm::vec2& getPosition() const;
	const float getRotation() const;
	const glm::vec2& getScale() const;

	const glm::mat4& getTranslationMatrix() const;
	const glm::mat4& getRotationMatrix() const;
	const glm::mat4& getScaleMatrix() const;
	const glm::mat4& getObjectMatrix() const;

	void setPosition(const glm::vec2& pos);
	void changePosition(const glm::vec2& offset);

	void setRotation(const float rot);
	void changeRotation(const float offset);

	void setScale(const glm::vec2& scale);
	void changeScale(const glm::vec2& offset);

	void draw(const Camera& cam);
};