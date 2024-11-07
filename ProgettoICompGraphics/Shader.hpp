#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

class Shader {
private:
	static std::string readShaderSource(const std::string& shaderFile);

	std::unordered_map<std::string, uint32_t> uniformLocations;
public:
	const uint32_t id;

	Shader(const std::string& fragmentFile, const std::string& vertexFile);
	~Shader();

	void activate() const;
	int32_t getUniformLocation(const std::string& uniform) const;
};