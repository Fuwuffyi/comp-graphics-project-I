#include "Asteroid.hpp"

#include "GameSettings.hpp"
#include "Shader.hpp"

#include <random>
#include <limits>

#include <glad/glad.h>

// Variables to randomly determine starting rotation
static std::random_device randomDevice;
static std::mt19937 randomEngine(randomDevice());
static std::uniform_real_distribution<float> startRotDist(0.0f, 360.0f);
static std::uniform_real_distribution<float> startAccel(-0.6f, 0.6f);
static std::uniform_real_distribution<float> rotAccel(-25.0f, 25.0f);
static std::uniform_real_distribution<float> spawnDistribution(-GameSettings::WORLD_SIZE * 0.7f, GameSettings::WORLD_SIZE * 0.7f);
static std::uniform_int_distribution<uint32_t> randomIdDistribution(0, std::numeric_limits<uint32_t>::max());

Asteroid::Asteroid(const Mesh* _mesh, const Shader* _shader, const glm::vec2& startPos, const glm::vec2& startScale)
:
	PhysicsGameObject(_mesh, _shader, startPos, startRotDist(randomEngine), startScale, 50.0f, glm::vec2(startAccel(randomEngine), startAccel(randomEngine)), rotAccel(randomEngine), 2.0f, 15.0f, 1.0f, 1.0f),
	uuid(randomIdDistribution(randomEngine))
{}

Asteroid::Asteroid(const Mesh* _mesh, const Shader* _shader, const glm::vec2 & startScale)
	:
	PhysicsGameObject(_mesh, _shader, glm::vec2(spawnDistribution(randomEngine), spawnDistribution(randomEngine)), startRotDist(randomEngine), startScale, 50.0f, glm::vec2(startAccel(randomEngine), startAccel(randomEngine)), rotAccel(randomEngine), 2.0f, 15.0f, 1.0f, 1.0f),
	uuid(randomIdDistribution(randomEngine))
{}

void Asteroid::randomizePosition() {
	this->setPosition(glm::vec2(spawnDistribution(randomEngine), spawnDistribution(randomEngine)));
}

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