#include "GameObject.h"

LogManager* GameObject::mLogManager;
TextureManager* GameObject::mTexManager;

GameObject::GameObject()
{
}

GameObject::GameObject(std::string meshFile, std::vector<Texture*> texes)
{
}

GameObject::GameObject(std::string meshFile)
{
}

GameObject::~GameObject()
{
}

void GameObject::loadModel(std::string fileName)
{
	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(fileName,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_FlipUVs |
		aiProcess_CalcTangentSpace
	);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		mLogManager->addLog(ELogType::E_ERROR, std::string(import.GetErrorString()));
		mLogManager->errorExit();
	}

	std::string directory = fileName.substr(0, fileName.find_last_of('/'));
	
	processNode(scene->mRootNode, scene);
}

void GameObject::processNode(aiNode * node, const aiScene * scene)
{
	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->mMeshes.push_back(processMesh(mesh, scene));
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene);
	}
}

Mesh * GameObject::processMesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	// vertices
	for (unsigned int i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;
		// position
		vertex.mPosition = vec3(
			mesh->mVertices[i].x, 
			mesh->mVertices[i].y,
			mesh->mVertices[i].z);

		// normals
		vertex.mNormal = vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z);

		// tangents
		vertex.mTangent = vec3(
			mesh->mTangents[i].x,
			mesh->mTangents[i].y,
			mesh->mTangents[i].z);

		// bitangents
		vertex.mBiTangent = vec3(
			mesh->mBitangents[i].x,
			mesh->mBitangents[i].y,
			mesh->mBitangents[i].z);

		// processing texture coords
		if (mesh->mTextureCoords[0])
		{
			vertex.mTexCoords = vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y);
		}
		else 
		{
			vertex.mTexCoords = vec2(0.0f, 0.0f);
		}
	}

	// indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			indices.push_back(face.mIndices[j]);
		}
	}

	// material textures


	return new Mesh(vertices, indices);
}
