#include "GUI.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.hpp"

static constexpr ImGuiWindowFlags configurationWindowFlags = ImGuiWindowFlags_AlwaysAutoResize;

static constexpr ImGuiWindowFlags scoreWindowFlags =
	ImGuiWindowFlags_NoMove
	| ImGuiWindowFlags_NoCollapse
	| ImGuiWindowFlags_AlwaysAutoResize
	| ImGuiWindowFlags_NoTitleBar;

GUI::GUI(GLFWwindow* window, const Shader* _bgShader, const Shader* _fgShader)
:
	bgShader(_bgShader),
	drawBg(true),
	rayMaxSteps(20),
	rayMinDist(0.01f),
	rayMaxDist(200.0f),
	starIterations(8),
	starVolumetricSteps(8),
	blackHoleRadius(0.2f),

	fgShader(_fgShader),
	drawFg(true),
	drawVignette(true),
	drawScanlines(true),
	scanlineScale(1.0f),
	transparency(0.2f),

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
	this->updateBg();
	this->updateFg();
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
		if (ImGui::SliderInt("Raymarching steps", &this->rayMaxSteps, 10, 200)) {
			this->updateBg();
		}
		if (ImGui::SliderFloat("Raymarching min threshold", &this->rayMinDist, 0.0001f, 0.5f)) {
			this->updateBg();
		}
		if (ImGui::SliderFloat("Raymarching max threshold", &this->rayMaxDist, 125.0f, 1000.0f)) {
			this->updateBg();
		}
		if (ImGui::SliderInt("Star iterations", &this->starIterations, 1, 20)) {
			this->updateBg();
		}
		if (ImGui::SliderInt("Star volumetrics", &this->starVolumetricSteps, 1, 20)) {
			this->updateBg();
		}
		if (ImGui::SliderFloat("Distortion radius", &this->blackHoleRadius, 0.0f, 1.0f)) {
			this->updateBg();
		}
	}
	if (ImGui::CollapsingHeader("Foreground settings")) {
		ImGui::Checkbox("Draw foreground", &this->drawFg);
		if (ImGui::Checkbox("Draw vignette", &this->drawVignette)) {
			this->updateFg();
		}
		if (ImGui::Checkbox("Draw scanlines", &this->drawScanlines)) {
			this->updateFg();
		}
		if (ImGui::SliderFloat("Scanline scale", &this->scanlineScale, 1.0f, 5.0f)) {
			this->updateFg();
		}
		if (ImGui::SliderFloat("Transparency", &this->transparency, 0.0f, 1.0f)) {
			this->updateFg();
		}
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

void GUI::updateBg() const {
	this->bgShader->activate();
	glUniform1ui(this->bgShader->getUniformLocation("rayStepCount"), this->rayMaxSteps);
	glUniform1f(this->bgShader->getUniformLocation("rayMinDist"), this->rayMinDist);
	glUniform1f(this->bgShader->getUniformLocation("rayMaxDist"), this->rayMaxDist);
	glUniform1ui(this->bgShader->getUniformLocation("starIterations"), this->starIterations);
	glUniform1ui(this->bgShader->getUniformLocation("starVolumetricSteps"), this->starVolumetricSteps);
	glUniform1f(this->bgShader->getUniformLocation("distortionRadiusPerc"), this->blackHoleRadius);
}

void GUI::updateFg() const {
	this->fgShader->activate();
	glUniform1ui(this->fgShader->getUniformLocation("bVignette"), this->drawVignette);
	glUniform1ui(this->fgShader->getUniformLocation("bScanlines"), this->drawScanlines);
	glUniform1f(this->fgShader->getUniformLocation("scanlineScale"), this->scanlineScale);
	glUniform1f(this->fgShader->getUniformLocation("transparency"), this->transparency);
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