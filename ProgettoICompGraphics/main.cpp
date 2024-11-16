#include "Shader.hpp"
#include "Mesh.hpp"
#include "HermiteMesh.hpp"
#include "Window.hpp"
#include "Camera.hpp"
#include "MeshReader.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Asteroid.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "GameSettings.hpp"
#include "GUI.hpp"
#include "LevelManager.hpp"

#include <glm/gtc/type_ptr.hpp>

int main() {
	// Initialize glfw
	if (!glfwInit()) {
		std::cerr << "Could not initialize glfw!" << std::endl;
		return EXIT_FAILURE;
	}
	// Set opengl version to V3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif // __APPLE__
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// Add double buffering
	glfwWindowHint(GLFW_DOUBLEBUFFER, GLFW_TRUE);
	// Eanable multisampling (MSAA 2x)
	glfwWindowHint(GLFW_SAMPLES, 2);
	// Create the window
	const std::string windowName = "Asteroids";
	Window window(windowName, 900, 900);
	window.setWindowActive();
	// Game camera
	Camera camera(glm::vec2(-0.5f, -0.5f), static_cast<float>(window.getHeight()) / static_cast<float>(window.getWidth()));
	// Create the shaders
	const Shader bgShader("bgFragShader.glsl", "bgVertShader.glsl");
	const Shader fgShader("fgFragShader.glsl", "fgVertShader.glsl");
	const Shader baseShader("baseFragShader.glsl", "baseVertShader.glsl");
	const Shader asteroidShader("asteroidFragShader.glsl", "asteroidVertShader.glsl");
	// Load meshes
	const Mesh windowMesh = MeshReader::loadBasicMesh("window_mesh.mesh", GL_TRIANGLES); // Used for BG and FG
	const HermiteMesh playerMesh = MeshReader::loadHermiteMesh("player_hermite.mesh", 15, true);
	const HermiteMesh bulletMesh = MeshReader::loadHermiteMesh("bullet_hermite.mesh", 5, true);
	const HermiteMesh asteroidMesh = MeshReader::loadHermiteMesh("asteroid_hermite.mesh", 10, true);
	// Setup gui
	GUI gui(window.getWindowPtr(), &bgShader, &fgShader);
	// Create game objects
	Player player(&playerMesh, &baseShader);
	std::vector<Bullet> bulletVector;
	std::vector<Asteroid> asteroidVector = LevelManager::generateLevel(&asteroidMesh, &asteroidShader, player, gui.getLevel());
	gui.setAsteroidsRemaining(static_cast<uint16_t>(asteroidVector.size()));
	// Set static uniforms
	bgShader.activate();
	glUniform1f(bgShader.getUniformLocation("worldSize"), GameSettings::WORLD_SIZE);
	// Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Draw/Game loop
	double prevTime = glfwGetTime();
	while (!window.shouldClose()) {
		// Deltatime calculation
		const double currTime = glfwGetTime();
		const float deltaTime = static_cast<float>(currTime - prevTime);
		prevTime = currTime;
		window.setTitle(windowName + " - " + std::to_string(1.0f / deltaTime));
		// Clear color buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// ----- Get new GUI frame -----
		gui.newFrame();
		// ----- Player Update stuff -----
		if (player.isAlive()) {
			player.update(deltaTime);
			if (Keyboard::keyWentDown(GLFW_KEY_SPACE)) {
				bulletVector.emplace_back(&bulletMesh, &baseShader, player.getPosition(), player.getRotation(), player.getHeadingVec() * 2.0f);
			}
			for (const Asteroid& asteroid : asteroidVector) {
				if (asteroid.getBoundingBox().checkCollisions(player.getBoundingBox())) {
					player.setDead(true);
				}
			}
		}
		// ----- Bullet Update stuff -----
		for (uint32_t i = static_cast<uint32_t>(bulletVector.size()); i > 0; --i) {
			Bullet& bullet = bulletVector[i - 1];
			bullet.update(deltaTime);
			if (bullet.getShouldDelete()) {
				bulletVector.erase(bulletVector.begin() + (i - 1));
			}
		}
		// ----- Asteroid Update stuff -----
		for (uint32_t i = static_cast<uint32_t>(asteroidVector.size()); i > 0; --i) {
			Asteroid& asteroid = asteroidVector[i - 1];
			asteroid.update(deltaTime);
			for (uint32_t j = static_cast<uint32_t>(bulletVector.size()); j > 0; --j) {
				const Bullet& bullet = bulletVector[j - 1];
				if (asteroid.getBoundingBox().checkCollisions(bullet.getBoundingBox())) {
					const float origScale = asteroid.getScale().x;
					const glm::vec2 newScale = glm::vec2(origScale) * 0.5f;
					const glm::vec2 newPos = asteroid.getPosition();
					bulletVector.erase(bulletVector.begin() + (j - 1));
					asteroidVector.erase(asteroidVector.begin() + (i - 1));
					if (newScale.x > GameSettings::ASTEROID_MIN_SCALE) {
						asteroidVector.emplace_back(&asteroidMesh, &asteroidShader, newPos, newScale);
						asteroidVector.emplace_back(&asteroidMesh, &asteroidShader, newPos, newScale);
					}
					gui.setAsteroidsRemaining(static_cast<uint16_t>(asteroidVector.size()));
					gui.addScore(static_cast<uint32_t>((origScale / GameSettings::ASTEROID_MAX_SCALE) * GameSettings::ASTEROID_MAX_SCORE));
					break;
				}
			}
		}
		if (gui.getAsteroidsRemaining() == 0) {
			gui.setLevel(gui.getLevel() + 1);
			asteroidVector = LevelManager::generateLevel(&asteroidMesh, &asteroidShader, player, gui.getLevel());
		}
		// Update camera
		camera.setPosition(player.getPosition());
		camera.changeAspectRatio(static_cast<float>(window.getHeight()) / static_cast<float>(window.getWidth()));
		camera.updateCameraMatrix();
		// ----- Draw Background -----
		if (gui.getDrawBg()) {
			bgShader.activate();
			glUniform2f(bgShader.getUniformLocation("playerPos"), player.getPosition().x, player.getPosition().y);
			glUniform1f(bgShader.getUniformLocation("timer"), static_cast<float>(glfwGetTime()));
			glUniform1f(bgShader.getUniformLocation("invAspectRatio"), camera.getInvAspectRatio());
			glUniform2f(bgShader.getUniformLocation("cameraPos"), camera.getPosition().x, camera.getPosition().y);
			windowMesh.draw();
		}
		// ----- Draw objects -----
		for (const Bullet& bullet : bulletVector) {
			bullet.draw(camera);
		}
		for (const Asteroid& asteroid : asteroidVector) {
			asteroid.draw(camera);
		}
		player.draw(camera);
		// ----- Draw foreground -----
		if (gui.getDrawFg()) {
			fgShader.activate();
			glUniform1f(fgShader.getUniformLocation("timer"), static_cast<float>(glfwGetTime()));
			windowMesh.draw();
		}
		// ----- Render GUI -----
		gui.render();
		// Swap buffers and poll events
		window.swapBuffers();
		glfwPollEvents();
	}
	return EXIT_SUCCESS;
}