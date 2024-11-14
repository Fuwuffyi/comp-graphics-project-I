#pragma once

#include <iostream>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window {
private:
	static void framebufferSizeCallback(GLFWwindow* window, const int32_t newWidth, const int32_t newHeight);

	std::string title;
	uint32_t width;
	uint32_t height;
	GLFWwindow* glWindow;
public:
	Window(const std::string& _title, const uint32_t _width, const uint32_t _height, const bool resizable = true);
	~Window();

	uint32_t getWidth() const;
	uint32_t getHeight() const;
	GLFWwindow* getWindowPtr() const;
	std::string getTitle() const;
	void setTitle(const std::string& _title);

	void setWindowActive() const;
	bool shouldClose() const;
	void swapBuffers() const;
private:
	void setWidth(const uint32_t _width);
	void setHeight(const uint32_t _height);
};