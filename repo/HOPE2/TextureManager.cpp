#include "TextureManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

LogManager* TextureManager::mLogManager;

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

void TextureManager::addToMaterial(Material * mat, Texture tex, int num)
{
}


std::vector<Texture>* TextureManager::getTextures(int num, Material* mat)
{
	switch (num)
	{
	case 1:
		return &mat->mDiffs;
		break;
	case 2:
		return &mat->mOpacs;
		break;
	case 3:
		return &mat->mNorms;
		break;
	case 4:
		return &mat->mSpecs;
		break;
	case 5:
		return &mat->mAmbients;
		break;
	default:
		return nullptr;
		break;
	}
	return nullptr;
}

Material * TextureManager::getMaterials(std::string matName)
{
	return nullptr;
}

void TextureManager::loadImage(const char * filename, E_TEX_TYPE type)
{
	Texture tmpTex;

	tmpTex.mTextureName = std::string(filename);
	glGenTextures(1, &tmpTex.mTextureID);
	glBindTexture(GL_TEXTURE_2D, tmpTex.mTextureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	
	int width, height, nrChannels;
	unsigned char* imageData = stbi_load(filename, &width, &height, &nrChannels, 0);

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
		mLogManager->addLog(ELogType::E_ERROR, "Failed to load image " + std::string(filename) + ".");
		mLogManager->errorExit();
	}

	switch (type)
	{
	case E_TEX_TYPE::DIFFUSE:
		
		break;
	case E_TEX_TYPE::OPACITY:
		break;
	case E_TEX_TYPE::NORMAL:
		break;
	case E_TEX_TYPE::SPECULAR:
		break;
	case E_TEX_TYPE::AMBIENT:
		break;
	default:
		break;
	}

	this->mTextures.push_back(tmpTex);
}
