#include "ResourceManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"
#include "LogManager.h"
std::vector<HObject> ResourceManager::hObject;
std::vector<HTexture> ResourceManager::hTexture;
std::vector<HMaterial> ResourceManager::hMaterial;
std::vector<unsigned int> ResourceManager::hAudio;
std::vector<long> ResourceManager::hResources;

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

unsigned int ResourceManager::loadMeshFile(std::string fileName)
{
	Assimp::Importer import;
	const aiScene * scene = import.ReadFile(fileName,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_FlipUVs);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) 
	{
		// debug Info
		LogManager::addLog(ELogType::E_ERROR, std::string(import.GetErrorString()));
		LogManager::errorExit();
	}

	std::string directory = fileName.substr(0, fileName.find_last_of('/'));

	HObject newObject;

	processNode(scene->mRootNode, scene, fileName, directory, &newObject);

	// store all the material id at the HObject class to be used at higher level heriachy later, to bypass the resourceManager Dependency Issue.
	for (unsigned int i = 0; i < newObject.getMeshNum(); i++)
	{
		newObject.pushBack(newObject.getMatAtMeshAt(i));
	}

	newObject.setRID(hObject.size());
	newObject.setType(1);
	hResources.push_back(newObject.getRID());
	hObject.push_back(newObject);
	return hObject.size() - 1;
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
		LogManager::addLog(ELogType::E_ERROR, "Failed to load image " + std::string(fileName));
		LogManager::errorExit();
	}
	tex.setRID(hTexture.size());
	tex.setType(2);
	hTexture.push_back(tex);
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
	hMaterial.push_back(mat);
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
	hMaterial.push_back(mat);
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

	// load in indices
	for (unsigned int i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++)
		{
			newMesh.pushBack(face.mIndices[j]);
		}
	}

	// load in bones
	for (unsigned int i = 0; i < mesh->mNumBones; i++)
	{
		aiBone* bone = mesh->mBones[i];  
		for (unsigned int j = 0; j < bone->mNumWeights; j++)
		{
			// get bone name
			aiVertexWeight weight = mesh->mBones[i]->mWeights[j];
			vertex* v = newMesh.getVertex(weight.mVertexId);
			if (v->mBone1.mBoneName == "None")
			{
				v->mBone1.mBoneName = bone->mName.C_Str();
				v->mBone1.mWeight = weight.mWeight;
				break;
			}
			else if (v->mBone2.mBoneName == "None") 
			{
				v->mBone2.mBoneName = bone->mName.C_Str();
				v->mBone2.mWeight = weight.mWeight;
				break;
			}
			else if (v->mBone3.mBoneName == "None") 
			{
				v->mBone3.mBoneName = bone->mName.C_Str();
				v->mBone3.mWeight = weight.mWeight;
				break;
			}
			else if(v->mBone4.mBoneName == "None")
			{
				v->mBone4.mBoneName = bone->mName.C_Str();
				v->mBone4.mWeight = weight.mWeight;
				break;
			}
		}
	}

	// load in materials
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
