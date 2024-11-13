#include "Window.hpp"
#include "Camera.hpp"
#include "MeshReader.hpp"
#include "Keyboard.hpp"
#include "Mouse.hpp"
#include "Player.hpp"
#include "Bullet.hpp"

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
	// Load meshes
	const Mesh windowMesh = MeshReader::loadBasicMesh("window_mesh.mesh", GL_TRIANGLES); // Used for BG and FG
	const HermiteMesh playerMesh = MeshReader::loadHermiteMesh("player_hermite.mesh", 25);
	const HermiteMesh bulletMesh = MeshReader::loadHermiteMesh("bullet_hermite.mesh", 5);
	// Create game objects
	Player player(&playerMesh, &baseShader);
	// Object vectors
	std::vector<Bullet> bulletVector;
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
		// ----- Player Input -----
		player.update(deltaTime);
		if (Keyboard::keyWentDown(GLFW_KEY_SPACE)) {
			bulletVector.emplace_back(&bulletMesh, &baseShader, player.getPosition(), player.getRotation(), player.getHeadingVec() * 2.0f);
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
		for (Bullet& bullet : bulletVector) {
			bullet.update(deltaTime);
			bullet.draw(camera);
		}
		bulletVector.erase(std::remove_if(
				bulletVector.begin(), 
				bulletVector.end(), 
				[](const Bullet& bullet) { return bullet.getShouldDelete(); }
			), 
			bulletVector.end()
		);
		player.draw(camera);
		// ----- Draw foreground -----
		fgShader.activate();
		glUniform1f(fgShader.getUniformLocation("timer"), static_cast<float>(glfwGetTime()));
		windowMesh.draw();
		// Swap buffers and poll events
		window.swapBuffers();
		glfwPollEvents();
	}
	return EXIT_SUCCESS;
}