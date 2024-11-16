#pragma once

#include <iostream>
#include <cstdint>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/**
 * Class that rapresents a glfw window.
 */
class Window {
private:
	/**
	 * Callback for when the window gets resized.
	 * 
	 * \param window The current window.
	 * \param newWidth The new window's width.
	 * \param newHeight The new window's height.
	 */
	static void framebufferSizeCallback(GLFWwindow* window, const int32_t newWidth, const int32_t newHeight);

	std::string title;
	uint32_t width;
	uint32_t height;
	GLFWwindow* glWindow;
public:
	/**
	 * Creates a new window.
	 * 
	 * \param _title The window's title.
	 * \param _width The window's starting width.
	 * \param _height The window's starting height.
	 * \param resizable Flag to check if the window should be resizable.
	 */
	Window(const std::string& _title, const uint32_t _width, const uint32_t _height, const bool resizable = true);

	/**
	 * Deallocates the memory allocated by GLFW.
	 * 
	 */
	~Window();

	/**
	 * Getter for the window's width.
	 *
	 * \return The window's current width.
	 */
	uint32_t getWidth() const;
	
	/**
	 * Getter for the window's height.
	 * 
	 * \return The window's current height.
	 */
	uint32_t getHeight() const;
	
	/**
	 * Getter for the window's glfw window pointer.
	 * 
	 * \return The glfwWindow pointer.
	 */
	GLFWwindow* getWindowPtr() const;

	/**
	 * Gets the current window's title.
	 * 
	 * \return The window's title
	 */
	std::string getTitle() const;

	/**
	 * Sets the window's title.
	 * 
	 * \param _title The new window title.
	 */
	void setTitle(const std::string& _title);

	/**
	 * Sets the window as active for drawing.
	 * 
	 */
	void setWindowActive() const;

	/**
	 * Checks whether the window should close or not.
	 * 
	 * \return True if the window should close.
	 */
	bool shouldClose() const;
	
	/**
	 * Calls glfw's swap buffers function.
	 * 
	 */
	void swapBuffers() const;
private:
	/**
	 * Sets the window's width, called by the callback.
	 * 
	 * \param _width The new window's width.
	 */
	void setWidth(const uint32_t _width);

	/**
	 * Sets the window's height, called by the callback.
	 *
	 * \param _width The new window's height.
	 */
	void setHeight(const uint32_t _height);
};