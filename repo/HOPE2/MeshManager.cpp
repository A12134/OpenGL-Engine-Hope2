#include "MeshManager.h"

LogManager* MeshManager::mLogManager;
TextureManager* MeshManager::mTexManager;

unsigned int MeshManager::addMesh(Mesh * newMesh)
{
	mMeshLibrary.push_back(newMesh);
	return this->mMeshLibrary.size() - 1;
	// return the index of the last element
}

unsigned int MeshManager::getMeshID(std::string meshName)
{
	for (unsigned int i = 0; i < this->mMeshLibrary.size(); i++)
	{
		if (meshName == mMeshLibrary.at(i)->getName())
		{
			return i;
		}
	}
	return 99999;
}

void MeshManager::renderMesh(unsigned int ID, ShaderProgram * sp, mat4 model, mat4 view, mat4 projection, unsigned int MaterialID)
{
	this->mMeshLibrary.at(ID)->render(sp, model, view, projection, mTexManager->getMaterialByID(MaterialID));	// Material ID
}

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}

void MeshManager::loadModel(std::string fileName, MeshNode * rootNode)
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

	processNode(scene->mRootNode, scene, fileName, directory, rootNode);
}

void MeshManager::processNode(aiNode * node, const aiScene * scene, std::string fileName, std::string directory, MeshNode * hNode)
{
	MeshNode* currentNode = hNode;

	for (unsigned int i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		this->mMeshLibrary.push_back(processMesh(mesh, scene, fileName, directory, currentNode));
		currentNode->addMeshID(this->mMeshLibrary.size() - 1);
	}

	for (unsigned int i = 0; i < node->mNumChildren; i++)
	{
		processNode(node->mChildren[i], scene, fileName, directory, currentNode->addNewChild());
	}
}

Mesh * MeshManager::processMesh(aiMesh * mesh, const aiScene * scene, std::string fileName, std::string directory, MeshNode * hNode)
{
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;

	for (unsigned int  i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		// position
		vertex.mPosition = vec3(
			mesh->mVertices[i].x,
			mesh->mVertices[i].y,
			mesh->mVertices[i].z
		);

		// normals
		vertex.mNormal = vec3(
			mesh->mNormals[i].x,
			mesh->mNormals[i].y,
			mesh->mNormals[i].z
		);

		// tangents
		vertex.mTangent = vec3(
			mesh->mTangents[i].x,
			mesh->mTangents[i].y,
			mesh->mTangents[i].z
		);

		// bitangents
		vertex.mBiTangent = vec3(
			mesh->mBitangents[i].x,
			mesh->mBitangents[i].y,
			mesh->mBitangents[i].z
		);

		// UVs
		if (mesh->mTextureCoords[0])
		{
			vertex.mTexCoords = vec2(
				mesh->mTextureCoords[0][i].x,
				mesh->mTextureCoords[0][i].y
			);
		}
		else
		{
			vertex.mTexCoords = vec2(0.0f);
		}

		vertices.push_back(vertex);
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
	processTexture(mesh, scene, fileName, directory, hNode);
	return new Mesh(vertices, indices);
}

void MeshManager::processTexture(aiMesh * mesh, const aiScene * scene, std::string fileName, std::string directory, MeshNode * hNode)
{
	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		Material* hMat = mTexManager->createMaterial(mesh->mName.C_Str());

		// diffuse Maps
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_DIFFUSE, i, &str);
			std::string imagePath = directory + str.C_Str();
			mTexManager->loadImage(imagePath.c_str(), E_TEX_TYPE::DIFFUSE, hMat);
		}
		// specular maps
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_SPECULAR, i, &str);
			std::string imagePath = directory + str.C_Str();
			mTexManager->loadImage(imagePath.c_str(), E_TEX_TYPE::SPECULAR, hMat);
		}

		// normal maps
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_NORMALS); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_NORMALS, i, &str);
			std::string imagePath = directory + str.C_Str();
			mTexManager->loadImage(imagePath.c_str(), E_TEX_TYPE::NORMAL, hMat);
		}

		// amibent maps
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_AMBIENT); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_AMBIENT, i, &str);
			std::string imagePath = directory + str.C_Str();
			mTexManager->loadImage(imagePath.c_str(), E_TEX_TYPE::AMBIENT, hMat);
		}

		// opacity maps
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_OPACITY); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_OPACITY, i, &str);
			std::string imagePath = directory + str.C_Str();
			mTexManager->loadImage(imagePath.c_str(), E_TEX_TYPE::OPACITY, hMat);
		}
	}
	hNode->setMaterialID(mTexManager->getMaterialID(mesh->mName.C_Str()));
}
