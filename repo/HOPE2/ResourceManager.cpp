#include "ResourceManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"


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

	newObject.setRID(hObject.size());
	newObject.setType(1);
	this->hResources.push_back(newObject.getRID());
	this->hObject.push_back(newObject);
}

unsigned int ResourceManager::loadImageFile(const char* fileName)
{
	HTexture tex;
	tex.setTextureName(fileName);
	tex.createNew2DTexture();

	int width, height, nrChannels;
	unsigned char* imageData = stbi_load(fileName, &width, &height, &nrChannels, 0);
	
	if (imageData)
	{
		GLenum format;
		if (nrChannels == 1)
		{
			format = GL_RED;
		}
		else if (nrChannels == 3) 
		{
			format = GL_RGB;
		}
		else if (nrChannels == 4) 
		{
			format = GL_RGBA;
		}

		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, imageData);
		glGenerateMipmap(GL_TEXTURE_2D);
		stbi_image_free(imageData);
	}
	else 
	{
		//errorLog
	}
	tex.setRID(hTexture.size());
	tex.setType(2);
	this->hTexture.push_back(tex);
	return tex.getRID();
}

unsigned int ResourceManager::createMaterial(std::vector<const char*> files)
{
	HMaterial mat;
	for (unsigned int i = 0; i < files.size(); i++)
	{
		mat.setTextureSlot(i, loadImageFile(files.at(i)));
	}
	mat.setRID(hMaterial.size());
	mat.setType(3);
	this->hMaterial.push_back(mat);
	return mat.getRID();
}

unsigned int ResourceManager::createMaterial(std::vector<unsigned int> textures)
{
	HMaterial mat;
	for (unsigned int i = 0; i < textures.size(); i++)
	{
		mat.setTextureSlot(i, textures.at(i));
	}
	mat.setRID(hMaterial.size());
	mat.setType(3);
	this->hMaterial.push_back(mat);
	return mat.getRID();
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

	// if there is any material defined, acquire all image pathes and load them into a material
	if (mesh->mMaterialIndex >= 0)
	{
		std::vector<const char*> files;
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		
		// diffuse
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_DIFFUSE, i, &str);
			std::string imagePath = directory + str.C_Str();
			files.push_back(imagePath.c_str());
		}
		// specular
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_SPECULAR); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_SPECULAR, i, &str);
			std::string imagePath = directory + str.C_Str();
			files.push_back(imagePath.c_str());
		}
		// normal,  note: the assimp label the normal map as height map
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_HEIGHT); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_HEIGHT, i, &str);
			std::string imagePath = directory + str.C_Str();
			files.push_back(imagePath.c_str());
		}
		// opacity
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_OPACITY); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_OPACITY, i, &str);
			std::string imagePath = directory + str.C_Str();
			files.push_back(imagePath.c_str());
		}
		// displacement
		for (unsigned int i = 0; i < material->GetTextureCount(aiTextureType_DISPLACEMENT); i++)
		{
			aiString str;
			material->GetTexture(aiTextureType_DISPLACEMENT, i, &str);
			std::string imagePath = directory + str.C_Str();
			files.push_back(imagePath.c_str());
		}

		// load into material
		newMesh.setMaterialID(createMaterial(files));
	}
	return newMesh;
}
