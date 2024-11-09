#include "Window.hpp"
#include "Camera.hpp"
#include "MeshReader.hpp"
#include "GameObject.hpp"

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
	// Eanable multisampling (MSAA 4x)
	glfwWindowHint(GLFW_SAMPLES, 4);
	// Create the window
	Window window("Test window", 1600, 900);
	window.setWindowActive();
	// Game camera
	Camera camera(glm::vec2(-0.5f, -0.5f));
	// Window plane mesh
	const Mesh squareMesh = MeshReader::loadBasicMesh("window_mesh.mesh", GL_TRIANGLES);
	// Create the shaders
	const Shader bgShader("bgFragShader.glsl", "bgVertShader.glsl");
	const Shader fgShader("fgFragShader.glsl", "fgVertShader.glsl");
	const Shader baseShader("baseFragShader.glsl", "baseVertShader.glsl");
	// Set some static uniforms (the camera's projection matrix does not change)
	bgShader.activate();
	glUniformMatrix4fv(bgShader.getUniformLocation("camProjMat"), 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));
	fgShader.activate();
	glUniformMatrix4fv(fgShader.getUniformLocation("camProjMat"), 1, GL_FALSE, glm::value_ptr(camera.getProjectionMatrix()));
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
		// Clear color buffer
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// ----- Update game logic stuff -----
		
		// Update camera
		camera.updateCameraMatrix();
		// ----- Draw Background -----
		bgShader.activate();
		glUniform1f(bgShader.getUniformLocation("timer"), static_cast<float>(glfwGetTime()));
		glUniform2f(bgShader.getUniformLocation("cameraPos"), camera.getPosition().x, camera.getPosition().y);
		squareMesh.draw();
		// ----- Draw objects -----
		
		// ----- Draw foreground -----
		fgShader.activate();
		glUniform1f(fgShader.getUniformLocation("timer"), static_cast<float>(glfwGetTime()));
		squareMesh.draw();
		// Swap buffers and poll events
		window.swapBuffers();
		glfwPollEvents();
	}
	return EXIT_SUCCESS;
}