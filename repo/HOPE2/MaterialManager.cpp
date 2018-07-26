#include "MaterialManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

LogManager* MaterialManager::mLogManager;

MaterialManager::MaterialManager()
{
}


MaterialManager::~MaterialManager()
{
}

unsigned int MaterialManager::addMaterial(Material * mat)
{
	this->mMaterialLibrary.push_back(mat);
	return this->mMaterialLibrary.size()-1;
}

void MaterialManager::addTextureToMat(unsigned int matID, unsigned int texture, E_TEX_TYPE type)
{
	switch (type)
	{
	case E_TEX_TYPE::DIFFUSE:
		this->mMaterialLibrary.at(matID)->mDiffs.push_back(texture);
		break;
	case E_TEX_TYPE::OPACITY:
		this->mMaterialLibrary.at(matID)->mOpacs.push_back(texture);
		break;
	case E_TEX_TYPE::NORMAL:
		this->mMaterialLibrary.at(matID)->mNorms.push_back(texture);
		break;
	case E_TEX_TYPE::SPECULAR:
		this->mMaterialLibrary.at(matID)->mSpecs.push_back(texture);
		break;
	case E_TEX_TYPE::AMBIENT:
		this->mMaterialLibrary.at(matID)->mAmbients.push_back(texture);
		break;
	default:
		break;
	}
}

unsigned int MaterialManager::getMaterialID(std::string name)
{
	for (unsigned int i = 0; i < this->mMaterialLibrary.size(); i++)
	{
		if (this->mMaterialLibrary.at(i)->mName == name)
		{
			return i;
		}
	}
	return 99999;
}

unsigned int MaterialManager::loadImage(const char * file)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);
	glBindTexture(GL_TEXTURE_2D, textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);

	int width, height, nrChannels;
	unsigned char* imageData = stbi_load(file, &width, &height, &nrChannels, 0);

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
		mLogManager->addLog(ELogType::E_ERROR, "Failed to load image " + std::string(file) + ".");
		mLogManager->errorExit();
	}
	return textureID;
}
