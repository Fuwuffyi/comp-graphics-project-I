#include <glm/gtc/type_ptr.hpp>

#include "Window.hpp"
#include "Camera.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"

int main() {
	// Initialize glfw
	if (!glfwInit()) {
		std::cerr << "Could not initialize glfw!" << std::endl;
		return -1;
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
	// Create the window
	Window window("Test window", 800, 800);
	window.setWindowActive();
	// Create a test camera
	Camera cam(glm::vec2(0.0f));
	// Test to draw some stuff
	const std::vector<Vertex> vertices = {
		Vertex { glm::vec2(0.5f, 0.5f), glm::vec4(1.0f, 0.0f, 0.0f, 0.3f) },
		Vertex { glm::vec2(0.0f, 0.0f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) },
		Vertex { glm::vec2(0.5f, 0.0f), glm::vec4(0.5f, 1.0f, 0.5f, 1.0f) },
		Vertex { glm::vec2(0.0f, 0.5f), glm::vec4(1.0f, 1.0f, 1.0f, 1.0f) }
	};
	const std::vector<uint32_t> indices = {
		0, 1, 2,
		0, 1, 3
	};
	// Testing mesh
	const Mesh square(vertices, indices);
	// Create shader
	const Shader shader("fragmentSource.glsl", "vertexSource.glsl");
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
		glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		// Update camera
		cam.setPosition(cam.getPosition() + glm::vec2(0.1f, 0.0f) * deltaTime);
		cam.updateCameraMatrix();
		// Activate shader (and pass camera to shader)
		shader.activate();
		glUniformMatrix4fv(shader.getUniformLocation("camMatrix"), 1, GL_FALSE, glm::value_ptr(cam.getCameraMatrix()));
		// Draw mesh
		square.draw(GL_TRIANGLES);
		// Swap buffers and poll events
		window.swapBuffers();
		glfwPollEvents();
	}
	return 0;
}