/*
TODO: discard this class
*/

#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H
#include "LogManager.h"
#include "Mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>
#include <vector>
struct Meshes 
{
	std::string mLODID;
	std::string mName;
	std::vector<Mesh*> mMeshes;
};
class MeshManager
{
private:
	std::vector<Meshes> mMeshCollection;
public:
	static LogManager* mLogManager;
public:
	MeshManager();
	~MeshManager();

	void loadMeshes(std::string LODID, std::string fileName);

private:
	void processNode(aiNode* node, const aiScene* scene, std::vector<Mesh*>* tmpMeshes);

	Mesh* processMesh(aiMesh* mesh, const aiScene* scene);

public:
	std::vector<Mesh*>* getMeshes(std::string LODID, std::string meshName);
};
#endif

