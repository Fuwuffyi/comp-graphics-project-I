#include "GUI.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

static constexpr ImGuiWindowFlags configurationWindowFlags = ImGuiWindowFlags_AlwaysAutoResize;

static constexpr ImGuiWindowFlags scoreWindowFlags =
	ImGuiWindowFlags_NoMove
	| ImGuiWindowFlags_NoCollapse
	| ImGuiWindowFlags_AlwaysAutoResize
	| ImGuiWindowFlags_NoTitleBar;

GUI::GUI(GLFWwindow* window)
:
	drawFg(true),
	drawBg(true),

	score(0),
	level(1),
	asteroidsRemaining(0)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	(void)io;
	ImGui::StyleColorsDark();
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init("#version 330");
}

GUI::~GUI() {
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void GUI::newFrame() const {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
}

void GUI::render() {
	// Configuration window setup
	ImGui::Begin("Configuration", nullptr, configurationWindowFlags);
	if (ImGui::CollapsingHeader("Background settings")) {
		ImGui::Checkbox("Draw background", &this->drawBg);
	}
	if (ImGui::CollapsingHeader("Foreground settings")) {
		ImGui::Checkbox("Draw foreground", &this->drawFg);
	}
	ImGui::End();
	// Scoring window setup
	ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
	ImGui::Begin("Level Info", nullptr, scoreWindowFlags);
	ImGui::Text("Score: %.8u", this->score);
	ImGui::Text("Level: %.2u", this->level);
	ImGui::Text("Asteroids Left: %.2u", this->asteroidsRemaining);
	ImGui::End();
	// Finish rendering
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

bool GUI::getDrawBg() const {
	return this->drawBg;
}

bool GUI::getDrawFg() const {
	return this->drawFg;
}

uint32_t GUI::getScore() const {
	return this->score;
}

uint16_t GUI::getLevel() const {
	return this->level;
}

uint16_t GUI::getAsteroidsRemaining() const {
	return this->asteroidsRemaining;
}

void GUI::setScore(const uint32_t _score) {
	this->score = _score;
}

void GUI::addScore(const uint32_t _score) {
	this->score += _score;
}

void GUI::setLevel(const uint16_t _level) {
	this->level = _level;
}

void GUI::setAsteroidsRemaining(const uint16_t _asteroidsRemaining) {
	this->asteroidsRemaining = _asteroidsRemaining;
}