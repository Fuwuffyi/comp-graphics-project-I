#pragma once

#include <string>

/**
 * Forward declaration for the Mesh class.
 */
class Mesh;

/**
 * Forward declaration for the HermiteMesh class.
 */
class HermiteMesh;

/**
 * A namespace holding functions to generate meshes from given files.
 */
namespace MeshReader {
	/**
	 * Creates a mesh from the data of a given file.
	 *
	 * \param filename The file containing the mesh's information.
	 * \param renderType The render type of the object.
	 * \return The generated mesh from the file.
	 */
    Mesh loadBasicMesh(const std::string& filename, const uint32_t renderType);

	/**
	 * Creates a hermite curve mesh from the data of a given file.
	 *
	 * \param filename The file containing the mesh's information.
	 * \param resolutionSteps The steps of interpolation for the curve.
	 * \param filled Flag to check if the curve must be filled.
	 * \return The generated hermite mesh from the file.
	 */
    HermiteMesh loadHermiteMesh(const std::string& filename, const uint32_t resolutionSteps, const bool filled);
};