#pragma once

#include <GLFW/glfw3.h>

class Mouse {
public:
	static void cursorPosCallback(GLFWwindow* window, const double _x, const double _y);
	static void mouseButtonCallback(GLFWwindow* window, const int32_t button, const int32_t action, const int32_t mods);
	static void mouseWheelCallback(GLFWwindow* window, const double _dx, const double _dy);
	static float getMouseX();
	static float getMouseY();
	static float getDx();
	static float getDy();
	static float getScrollDx();
	static float getScrollDy();
	static bool button(const int32_t button);
	static bool buttonChanged(const int32_t button);
	static bool buttonWentUp(const int32_t button);
	static bool buttonWentDown(const int32_t button);

private:
	Mouse();

	static float x;
	static float y;
	static float lastX;
	static float lastY;
	static float dx;
	static float dy;
	static float scrollDx;
	static float scrollDy;
	static bool firstMouse;
	static bool buttons[];
	static bool buttonsChanged[];
};