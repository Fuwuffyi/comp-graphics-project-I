#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

int main() {
    // Initialize glfw
    if (!glfwInit()) {
        std::cerr << "Could not initialize glfw!" << std::endl;
        exit(EXIT_FAILURE);
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
        exit(EXIT_FAILURE);
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
    // Draw/Game loop
    while (!glfwWindowShouldClose(window)) {
        glClearColor(0.0, 0.0, 0.0, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}