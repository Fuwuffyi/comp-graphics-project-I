#include "Asteroid.hpp"

#include "GameSettings.hpp"
#include "Shader.hpp"

#include <random>
#include <limits>

#include <glad/glad.h>

// Variables to randomly determine starting rotation
static std::random_device rd;
static std::mt19937 e2(rd());
static std::uniform_real_distribution<float> startRotDist(0.0f, 360.0f);
static std::uniform_real_distribution<float> startAccel(-0.6f, 0.6f);
static std::uniform_real_distribution<float> rotAccel(-25.0f, 25.0f);
static std::uniform_real_distribution<float> spawnDistribution(-GameSettings::WORLD_SIZE + 0.05f, GameSettings::WORLD_SIZE - 0.05f);
static std::uniform_int_distribution<uint32_t> randomIdDistribution(0, std::numeric_limits<uint32_t>::max());

Asteroid::Asteroid(const Mesh* _mesh, const Shader* _shader, const glm::vec2& startPos, const glm::vec2& startScale)
:
	PhysicsGameObject(_mesh, _shader, startPos, startRotDist(e2), startScale, 50.0f, glm::vec2(startAccel(e2), startAccel(e2)), rotAccel(e2), 2.0f, 15.0f, 1.0f, 1.0f),
	uuid(randomIdDistribution(e2))
{}

Asteroid::Asteroid(const Mesh * _mesh, const Shader * _shader, const glm::vec2 & startScale)
	:
	PhysicsGameObject(_mesh, _shader, glm::vec2(spawnDistribution(e2), spawnDistribution(e2)), startRotDist(e2), startScale, 50.0f, glm::vec2(startAccel(e2), startAccel(e2)), rotAccel(e2), 2.0f, 15.0f, 1.0f, 1.0f),
	uuid(randomIdDistribution(e2))
{}

void Asteroid::update(const float deltaTime) {
	this->tickPhysics(deltaTime);
	if (glm::length(this->getPosition()) > GameSettings::WORLD_SIZE) {
		this->setPosition(-this->getPosition());
	}
}

void Asteroid::draw(const Camera& cam) const {
	this->shader->activate();
	glUniform1ui(this->shader->getUniformLocation("uuid"), this->uuid);
	PhysicsGameObject::draw(cam);
}