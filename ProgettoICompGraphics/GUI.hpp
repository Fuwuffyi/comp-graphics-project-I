#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <cstdint>

class GUI {
private:
	bool drawBg;
	bool drawFg;

	uint32_t score;
	uint16_t level;
	uint16_t asteroidsRemaining;
public:
	GUI(GLFWwindow* window);
	~GUI();

	void newFrame() const;
	void render();

	// Config
	bool getDrawBg() const;
	bool getDrawFg() const;
	// Score display and such
	uint32_t getScore() const;
	uint16_t getLevel() const;
	uint16_t getAsteroidsRemaining() const;
	void setScore(const uint32_t _score);
	void setLevel(const uint16_t _level);
	void setAsteroidsRemaining(const uint16_t _asteroidsRemaining);
};