#pragma once

#include <string>
#include <cstdint>
#include <unordered_map>

/**
 * Class holding information of a shader.
 */
class Shader {
private:
	/**
	 * Reads the content of a file to compile the shader in OpenGL.
	 * 
	 * \param shaderFile The file to read.
	 * \return The string containing the source of the file.
	 */
	static std::string readShaderSource(const std::string& shaderFile);

	/**
	 * Checks and prints error of given shader sources.
	 * 
	 * \param shaderType The type of the shader to log.
	 * \param shaderId The id of the shader to check errors for.
	 */
	void checkErrors(const std::string& shaderType, const uint32_t shaderId) const;

	std::unordered_map<std::string, uint32_t> uniformLocations; // Contains all of the uniform variable locations
public:
	const uint32_t id;

	/**
	 * Creates a new shader program from a fragment and vertex shader.
	 * 
	 * \param fragmentFile The fragment shader's file location.
	 * \param vertexFile The vertex shader's file location.
	 */
	Shader(const std::string& fragmentFile, const std::string& vertexFile);

	/**
	 * Deallocates the GPU memory for this shader program.
	 * 
	 */
	~Shader();

	/**
	 * Activates the shader to use for all next rendered objects.
	 * 
	 */
	void activate() const;

	/**
	 * Getter for an uniform location within the shader.
	 * 
	 * \param uniform The uniform to get the location of.
	 * \return The uniform's location within the shader, -1 if it does not exist.
	 */
	int32_t getUniformLocation(const std::string& uniform) const;
};