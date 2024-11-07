#include <iostream>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
    GLFWwindow* window = glfwCreateWindow(800, 800, "Base window", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create the window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    // Set window active
    glfwMakeContextCurrent(window);
    // Load glad function pointers
    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        std::cerr << "Failed to load opengl function pointers!" << std::endl;
        glfwDestroyWindow(window);
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
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
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.3, 0.2, 0.3, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        shader.activate();
        square.draw(GL_TRIANGLES);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}