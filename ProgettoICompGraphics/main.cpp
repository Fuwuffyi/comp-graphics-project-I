#include "Window.hpp"
#include "Camera.hpp"
#include "MeshReader.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Asteroid.hpp"
#include "Player.hpp"
#include "Bullet.hpp"
#include "GUI.hpp"

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
	// Setup gui
	GUI gui(window.getWindowPtr());
	// Game camera
	Camera camera(glm::vec2(-0.5f, -0.5f), static_cast<float>(window.getHeight()) / static_cast<float>(window.getWidth()));
	// Create the shaders
	const Shader bgShader("bgFragShader.glsl", "windowVertShader.glsl");
	const Shader fgShader("fgFragShader.glsl", "windowVertShader.glsl");
	const Shader baseShader("baseFragShader.glsl", "baseVertShader.glsl");
	const Shader asteroidShader("baseFragShader.glsl", "asteroidVertShader.glsl");
	// Load meshes
	const Mesh windowMesh = MeshReader::loadBasicMesh("window_mesh.mesh", GL_TRIANGLES); // Used for BG and FG
	const HermiteMesh playerMesh = MeshReader::loadHermiteMesh("player_hermite.mesh", 15, true);
	const HermiteMesh bulletMesh = MeshReader::loadHermiteMesh("bullet_hermite.mesh", 5, true);
	const HermiteMesh asteroidMesh = MeshReader::loadHermiteMesh("asteroid_hermite.mesh", 20, true);
	// Create game objects
	Player player(&playerMesh, &baseShader);
	std::vector<Bullet> bulletVector;
	std::vector<Asteroid> asteroidVector;
	for (uint32_t i = 0; i < 2; ++i) {
		asteroidVector.emplace_back(&asteroidMesh, &asteroidShader, glm::vec2(0.0f), glm::vec2(0.1f), glm::vec2(0.0f));
	}
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
		player.update(deltaTime);
		if (Keyboard::keyWentDown(GLFW_KEY_SPACE)) {
			bulletVector.emplace_back(&bulletMesh, &baseShader, player.getPosition(), player.getRotation(), player.getHeadingVec() * 2.0f);
		}
		// ----- Bullet Update stuff -----
		for (uint32_t i = bulletVector.size(); i > 0; --i) {
			Bullet& bullet = bulletVector[i - 1];
			bullet.update(deltaTime);
			if (bullet.getShouldDelete()) {
				bulletVector.erase(bulletVector.begin() + (i - 1));
			}
		}
		// ----- Asteroid Update stuff -----
		for (uint32_t i = asteroidVector.size(); i > 0; --i) {
			Asteroid& asteroid = asteroidVector[i - 1];
			asteroid.update(deltaTime);
			for (uint32_t j = bulletVector.size(); j > 0; --j) {
				const Bullet& bullet = bulletVector[j - 1];
				if (asteroid.getBoundingBox().checkCollisions(bullet.getBoundingBox())) {
					const glm::vec2 newScale = asteroid.getScale() / 2.0f;
					bulletVector.erase(bulletVector.begin() + (j - 1));
					asteroidVector.erase(asteroidVector.begin() + (i - 1));
					asteroidVector.emplace_back(&asteroidMesh, &asteroidShader, glm::vec2(0.0f), newScale, glm::vec2(0.0f));
					asteroidVector.emplace_back(&asteroidMesh, &asteroidShader, glm::vec2(0.0f), newScale, glm::vec2(0.0f));
					break;
				}
			}
		}
		// Update camera
		camera.setPosition(player.getPosition());
		camera.changeAspectRatio(static_cast<float>(window.getHeight()) / static_cast<float>(window.getWidth()));
		camera.updateCameraMatrix();
		// ----- Draw Background -----
		bgShader.activate();
		glUniform1f(bgShader.getUniformLocation("timer"), static_cast<float>(glfwGetTime()));
		glUniform1f(bgShader.getUniformLocation("invAspectRatio"), camera.getInvAspectRatio());
		glUniform2f(bgShader.getUniformLocation("cameraPos"), camera.getPosition().x, camera.getPosition().y);
		windowMesh.draw();
		// ----- Draw objects -----
		for (const Bullet& bullet : bulletVector) {
			bullet.draw(camera);
		}
		for (const Asteroid& asteroid : asteroidVector) {
			asteroid.draw(camera);
		}
		player.draw(camera);
		// ----- Draw foreground -----
		fgShader.activate();
		glUniform1f(fgShader.getUniformLocation("timer"), static_cast<float>(glfwGetTime()));
		windowMesh.draw();
		// ----- Render GUI -----
		gui.render();
		// Swap buffers and poll events
		window.swapBuffers();
		glfwPollEvents();
	}
	return EXIT_SUCCESS;
}