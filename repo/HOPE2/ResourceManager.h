/*Manage all the functions related to in game resources*/
/*Load and unload all the resources					   */
#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H
#include "HMaterial.h"
#include "HObject.h"
#include "HTexture.h"
#include <vector>
// mesh related loading library
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
// image related loading library
#include "stb_image.h"
// audio related loading library
class ResourceManager
{
private:
	//Contains all the Resources
	std::vector<long> hResources;

	// Contains all the mesh index From Resource Vector
	std::vector<HObject> hObject;
	std::vector<HTexture> hTexture;
	std::vector<HMaterial> hMaterial;
	std::vector<unsigned int> hAudio;

public:
	ResourceManager();
	~ResourceManager();

	/*Start up the resource Manager*/
	void startUp();
	/*Shut down the resource Manager*/
	void shutDown();

	// Load in mesh files
	// It will load the skeleton and materials as well if those assets are exist inside the file
	void loadMeshFile(std::string fileName);

	// Load in image files
	// @para: file name
	// @return: the position inside the hTexture Vector;
	unsigned int loadImageFile(const char*  fileName);

	// @param: set of fileNames
	// @return: the Index of the material inside hMaterial vector
	unsigned int createMaterial(std::vector<const char*> files);

	// @param: set of texture indexes of hTexture vector
	// @return: the Index of the material inside hMaterial vector
	unsigned int createMaterial(std::vector<unsigned int> textures);

private:
	// Returns an unique RID by fileName
	long GenerateRID(std::string fileName);

	void processNode(aiNode* node, const aiScene * scene, std::string fileName, std::string directory, HObject* newObject);

	HMesh processMesh(aiMesh* mesh, const aiScene * scene, std::string fileName, std::string directory);
};
#endif

