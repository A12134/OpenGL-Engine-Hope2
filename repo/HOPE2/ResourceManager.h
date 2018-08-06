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
	std::vector<Resource> hResources;

	// Contains all the mesh index From Resource Vector
	std::vector<unsigned int> hObject;
	std::vector<unsigned int> hTexture;
	std::vector<unsigned int> hMaterial;
	std::vector<unsigned int> hAudio;

public:
	ResourceManager();
	~ResourceManager();

	/*Start up the resource Manager*/
	void startUp();
	/*Shut down the resource Manager*/
	void shutDown();

	// Load in mesh files
	void loadMeshFile(std::string fileName);

	// Load in image files
	void loadImageFile(std::string fileName);



private:
	// Returns an unique RID by fileName
	long GenerateRID(std::string fileName);
};
#endif

