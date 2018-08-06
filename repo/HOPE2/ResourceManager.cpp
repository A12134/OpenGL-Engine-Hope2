#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}

void ResourceManager::startUp()
{
}

void ResourceManager::shutDown()
{
}

void ResourceManager::loadMeshFile(std::string fileName)
{
	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(fileName,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		// debug Info
	}

	std::string directory = fileName.substr(0, fileName.find_last_of('/'));

	HObject newObject;

	processNode(scene->mRootNode, scene, fileName, directory, &newObject);

	newObject.setRID(hResources.size());
	this->hResources.push_back(newObject);
	this->hObject.push_back(hResources.size() - 1);
}

long ResourceManager::GenerateRID(std::string fileName)
{
	long hashVal = 3;
	for (int i = 0; i < fileName.length(); i++)
	{
		hashVal = hashVal * 7 + fileName[i];
	}
	return hashVal;
}

void ResourceManager::processNode(aiNode * node, const aiScene * scene, std::string fileName, std::string directory, HObject *newObject)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		newObject->pushBack(processMesh(mesh, scene, fileName, directory));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, fileName, directory, newObject);
	}
}

HMesh ResourceManager::processMesh(aiMesh * mesh, const aiScene * scene, std::string fileName, std::string directory)
{
	HMesh newMesh;

	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		vertex v;
		v.mPos = glm::vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		v.mNormal = glm::vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		if (mesh->mTextureCoords[0])
		{
			v.mUV = glm::vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else 
		{
			v.mUV = glm::vec2(0.0f);
		}

		newMesh.pushBack(v);
	}

	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			newMesh.pushBack(face.mIndices[j]);
		}
	}

	return newMesh;
}
