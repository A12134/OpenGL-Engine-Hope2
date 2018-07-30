#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H
#include "LogManager.h"
#include "Mesh.h"
#include <vector>
#include "ShaderProgram.h"
#include "MeshNode.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include "TextureManager.h"

class MeshManager
{
public:
	static LogManager* mLogManager;
	static TextureManager* mTexManager;

private:
	std::vector<Mesh*> mMeshLibrary;

public:
	unsigned int addMesh(Mesh* newMesh);
	unsigned int getMeshID(std::string meshName);
	void renderMesh(unsigned int ID, ShaderProgram* sp, mat4 model, mat4 view, mat4 projection, unsigned int MaterialID);
	MeshManager();
	~MeshManager();

	void loadModel(std::string fileName, MeshNode* rootNode);

private:
	void processNode(aiNode* node, const aiScene * scene, std::string fileName, std::string directory, MeshNode* hNode);

	Mesh* processMesh(aiMesh* mesh, const aiScene* scene, std::string fileName, std::string directory, MeshNode* hNode);

	void processTexture(aiMesh* mesh, const aiScene* scene, std::string fileName, std::string directory, MeshNode* hNode);
};
#endif

