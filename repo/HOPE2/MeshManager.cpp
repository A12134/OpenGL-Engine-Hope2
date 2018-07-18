#include "MeshManager.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

LogManager* MeshManager::mLogManager;

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
	mLogManager->addLog(ELogType::E_EVENT, "Unloading meshes");
	for (unsigned int i = 0; i < this->mMeshCollection.size(); i++)
	{
		for (unsigned int j = 0; j < this->mMeshCollection.at(i).mMeshes.size(); j++)
		{
			delete this->mMeshCollection.at(i).mMeshes.at(j);
			this->mMeshCollection.at(i).mMeshes.at(j) = nullptr;
		}
		mMeshCollection.at(i).mMeshes.clear();
		mMeshCollection.at(i).mMeshes = std::vector<Mesh*>();

		mMeshCollection.at(i) = Meshes();
	}
	mMeshCollection.clear();
	mMeshCollection = std::vector<Meshes>();
}

void MeshManager::loadMeshes(std::string LODID, std::string fileName)
{
	
	if (getMeshes(LODID, fileName))
	{
		mLogManager->addLog(ELogType::E_WARNING, "File " + fileName + " is already loaded.");
		return;
	}

	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(fileName,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		mLogManager->addLog(ELogType::E_ERROR, std::string(import.GetErrorString()) + ".");
		mLogManager->errorExit();
	}

	std::string directory = fileName.substr(0, fileName.find_last_of('/'));

	Meshes newMeshes;
	newMeshes.mLODID = LODID;
	newMeshes.mName = fileName;
	processNode(scene->mRootNode, scene, &newMeshes.mMeshes);
	this->mMeshCollection.push_back(newMeshes);
}

void MeshManager::processNode(aiNode * node, const aiScene * scene, std::vector<Mesh*>* tmpMeshes)
{
	// process all the node's meshes(if any)
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh * mesh = scene->mMeshes[node->mMeshes[i]];
		tmpMeshes->push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, tmpMeshes);
	}
}

Mesh * MeshManager::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		vec3 tmpVec;
		// vertices
		tmpVec.x = mesh->mVertices[i].x;
		tmpVec.y = mesh->mVertices[i].y;
		tmpVec.z = mesh->mVertices[i].z;
		vertex.mPosition = tmpVec;

		// normals
		tmpVec.x = mesh->mNormals[i].x;
		tmpVec.y = mesh->mNormals[i].y;
		tmpVec.z = mesh->mNormals[i].z;
		vertex.mNormal = tmpVec;

		// tangents
		tmpVec.x = mesh->mTangents[i].x;
		tmpVec.y = mesh->mTangents[i].y;
		tmpVec.z = mesh->mTangents[i].z;
		vertex.mTangent = tmpVec;

		// bitangents
		tmpVec.x = mesh->mBitangents[i].x;
		tmpVec.y = mesh->mBitangents[i].y;
		tmpVec.z = mesh->mBitangents[i].z;
		vertex.mBiTangent = tmpVec;

		// processing texture coords
		if (mesh->mTextureCoords[0])
		{
			vec2 tmpVec2;
			tmpVec2.x = mesh->mTextureCoords[0][i].x;
			tmpVec2.y = mesh->mTextureCoords[0][i].y;
			vertex.mTexCoords = tmpVec2;
		}
		else 
		{
			vertex.mTexCoords = vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// TODO process textures
	return new Mesh(vertices, indices);
}

std::vector<Mesh*>* MeshManager::getMeshes(std::string LODID, std::string meshName)
{
	// TODO hash table
	return nullptr;
}