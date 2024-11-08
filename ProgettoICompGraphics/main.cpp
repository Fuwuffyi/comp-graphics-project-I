#include "Window.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"

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
	const std::shared_ptr<Mesh> square = std::make_shared<Mesh>(vertices, indices, GL_TRIANGLES);
	// Create shader
	const std::shared_ptr<Shader> shader = std::make_shared<Shader>("fragmentSource.glsl", "vertexSource.glsl");
	// Testing game object capabilities
	const GameObject squareGobj(square, shader, glm::vec2(0.0f), 25.0f, glm::vec2(1.2f));
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
		// Update camera
		cam.setPosition(cam.getPosition() + glm::vec2(0.1f, 0.0f) * deltaTime);
		cam.updateCameraMatrix();
		// Draw game object
		squareGobj.draw(cam);
		// Swap buffers and poll events
		window.swapBuffers();
		glfwPollEvents();
	}
	return EXIT_SUCCESS;
}