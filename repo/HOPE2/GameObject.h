#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "LogManager.h"
#include "TextureManager.h"
#include <vector>
#include "Mesh.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class GameObject
{
public:
	static TextureManager* mTexManager;
	static LogManager* mLogManager;

private:
	std::vector<Mesh *> mMeshes;
	Material* mMaterial;
	std::vector<Texture *> mTexes;

public:
	GameObject();
	GameObject(std::string meshFile, Material* mat);
	// GameObject(model, texture)
	GameObject(std::string meshFile);
	// GameObject(model)	// obj file cames with texture
	~GameObject();

private:
	void loadModel(std::string fileName);
	void processNode(aiNode * node, const aiScene * scene, std::string fileName, std::string directory);
	Mesh* processMesh(aiMesh * mesh, const aiScene * scene, std::string fileName, std::string directory);

public:

};
#endif