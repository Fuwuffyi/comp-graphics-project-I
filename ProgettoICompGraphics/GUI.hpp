#pragma once

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <cstdint>

/**
 * Forward declaration for the Shader class.
 */
class Shader;

/**
 * Class containing ImGui related stuff.
 */
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
	/**
	 * Constructs everything needed for ImGui to work.
	 * 
	 * \param window The glfw window to attach to.
	 * \param _bgShader The background shader's pointer.
	 * \param _fgShader The foreground shader's pointer.
	 */
	GUI(GLFWwindow* window, const Shader* _bgShader, const Shader* _fgShader);

	/**
	 * Deallocates ImGui's memory.
	 * 
	 */
	~GUI();

	/**
	 * Function to request a new clean frame for ImGui.
	 * 
	 */
	void newFrame() const;

	/**
	 * Renders the GUI on the window.
	 * 
	 */
	void render();

	/**
	 * Updates all of the background shader's uniforms.
	 * 
	 */
	void updateBg() const;

	/**
	 * Updates all of the foreground shader's uniforms.
	 *
	 */
	void updateFg() const;
	
	/**
	 * Getter to check if it should draw the background.
	 * 
	 * \return True if it should draw the background.
	 */
	bool getDrawBg() const;

	/**
	 * Getter to check if it should draw the foreground.
	 *
	 * \return True if it should draw the foreground.
	 */
	bool getDrawFg() const;

	/**
	 * Getter for the player's score.
	 * 
	 * \return The player's score.
	 */
	uint32_t getScore() const;

	/**
	 * Getter for the player's level.
	 *
	 * \return The player's level.
	 */
	uint16_t getLevel() const;

	/**
	 * Getter for the number asteroids remaining in the level.
	 *
	 * \return The number asteroids remaining in the level.
	 */
	uint16_t getAsteroidsRemaining() const;

	/**
	 * Setter for the player's score number.
	 * 
	 * \param _score The new score value for the player.
	 */
	void setScore(const uint32_t _score);

	/**
	 * Adds a number to the player's score.
	 *
	 * \param _score The amount of score to add to the player.
	 */
	void addScore(const uint32_t _score);

	/**
	 * Sets the level for the player to beat.
	 * 
	 * \param _level The new game's level.
	 */
	void setLevel(const uint16_t _level);

	/**
	 * Set's the gui's asteroid remaining counter.
	 *  
	 * \param _asteroidsRemaining The new number of asteroids remaining.
	 */
	void setAsteroidsRemaining(const uint16_t _asteroidsRemaining);
};