#include "Window.hpp"

void Window::framebufferSizeCallback(GLFWwindow* window, const int32_t newWidth, const int32_t newHeight) {
	// Set window's object data on resize
	Window* windowObj = static_cast<Window*>(glfwGetWindowUserPointer(window));
	windowObj->setWidth(static_cast<uint32_t>(newWidth));
	windowObj->setHeight(static_cast<uint32_t>(newHeight));
	// Change viewport based on new data
	glViewport(0, 0, newWidth, newHeight);
}

Window::Window(const std::string& _title, const uint32_t _width, const uint32_t _height, const bool resizable)
	:
	title(_title.c_str()),
	width(_width),
	height(_height),
	glWindow(glfwCreateWindow(this->width, this->height, this->title.c_str(), nullptr, nullptr))
{
	if (!glWindow) {
		std::cerr << "Failed to create the window!" << std::endl;
		glfwTerminate();
		exit(-1);
	}
	// Set the window's owner to this object 
	glfwSetWindowUserPointer(this->glWindow, this);
	// Set window resize callback
	glfwSetFramebufferSizeCallback(this->glWindow, Window::framebufferSizeCallback);
}

Window::~Window() {
	glfwDestroyWindow(this->glWindow);
	glfwTerminate();
}

uint32_t Window::getWidth() const {
	return this->width;
}

uint32_t Window::getHeight() const {
	return this->height;
}

std::string Window::getTitle() const {
	return this->title;
}

void Window::setTitle(const std::string& title) {
	// TODO:
}

void Window::setWindowActive() const {
	glfwMakeContextCurrent(this->glWindow);
	// Load glad function pointers (every time it is set active, as gl version depends on the window)
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
		std::cerr << "Failed to load opengl function pointers!" << std::endl;
		glfwDestroyWindow(this->glWindow);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
}

bool Window::shouldClose() const {
	return glfwWindowShouldClose(this->glWindow);
}

void Window::swapBuffers() const {
	glfwSwapBuffers(this->glWindow);
}

void Window::setWidth(const uint32_t _width) {
	this->width = _width;
}

void Window::setHeight(const uint32_t _height) {
	this->height = _height;
}
