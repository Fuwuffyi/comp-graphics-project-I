#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <cstdint>

class Shader;

class GUI {
private:
	// BG Settings
	const Shader* bgShader;
	bool drawBg;
	int32_t rayMaxSteps;
	float rayMinDist;
	float rayMaxDist;
	int32_t starIterations;
	int32_t starVolumetricSteps;
	float blackHoleRadius;

	// FG Settings
	const Shader* fgShader;
	bool drawFg;
	bool drawVignette;
	bool drawScanlines;
	float scanlineScale;
	float transparency;

	// Player UI
	uint32_t score;
	uint16_t level;
	uint16_t asteroidsRemaining;
public:
	GUI(GLFWwindow* window, const Shader* _bgShader, const Shader* _fgShader);
	~GUI();

	void newFrame() const;
	void render();

	void updateBg() const;
	void updateFg() const;

	// Config
	bool getDrawBg() const;
	bool getDrawFg() const;
	// Score display and such
	uint32_t getScore() const;
	uint16_t getLevel() const;
	uint16_t getAsteroidsRemaining() const;
	void setScore(const uint32_t _score);
	void addScore(const uint32_t _score);
	void setLevel(const uint16_t _level);
	void setAsteroidsRemaining(const uint16_t _asteroidsRemaining);
};