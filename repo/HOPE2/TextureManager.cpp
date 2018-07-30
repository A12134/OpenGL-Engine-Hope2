#include "TextureManager.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "stb_image.h"

LogManager* TextureManager::mLogManager;

TextureManager::TextureManager()
{
	mMaterials = std::vector<Material>();
}


TextureManager::~TextureManager()
{
}

Material* TextureManager::createMaterial(std::string name)
{
	Material* ptr = getMaterials(name);
	if (ptr == nullptr) 
	{
		Material tmp;
		tmp.mName = name;
		this->mMaterials.push_back(tmp);
		return &this->mMaterials.back();
	}
	mLogManager->addLog(ELogType::E_WARNING, "Material name " + name + " already exist.");
	return ptr;
}

unsigned int TextureManager::getMaterialID(std::string name)
{
	for (unsigned int i = 0; i < this->mMaterials.size(); i++)
	{
		if (mMaterials.at(i).mName == name)
		{
			return i;
		}
	}
	mLogManager->addLog(ELogType::E_WARNING, "Material " + name + " does not exist. ");
	return 99999;
}

std::vector<Texture>* TextureManager::getTextures(E_TEX_TYPE type, Material* mat)
{
	if (mat != nullptr)
	{
		switch (type)
		{
		case E_TEX_TYPE::DIFFUSE:
			return &mat->mDiffs;
			break;
		case E_TEX_TYPE::OPACITY:
			return &mat->mOpacs;
			break;
		case E_TEX_TYPE::NORMAL:
			return &mat->mNorms;
			break;
		case E_TEX_TYPE::SPECULAR:
			return &mat->mSpecs;
			break;
		case E_TEX_TYPE::AMBIENT:
			return &mat->mAmbients;
			break;
		default:
			return nullptr;
			break;
		}
	}
	mLogManager->addLog(ELogType::E_WARNING, "Does not find the material.");
	return nullptr;
}

Material * TextureManager::getMaterials(std::string matName)
{
	for (unsigned int i = 0; i < this->mMaterials.size(); i++)
	{
		if (mMaterials.at(i).mName == matName)
		{
			return &mMaterials.at(i);
		}
	}
	mLogManager->addLog(ELogType::E_WARNING, "Material " + matName + " does not exist. ");
	return nullptr;
}

void TextureManager::loadImage(const char * filename, E_TEX_TYPE type, Material* mat)
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
		mat->mDiffs.push_back(tmpTex);
		break;
	case E_TEX_TYPE::OPACITY:
		mat->mOpacs.push_back(tmpTex);
		break;
	case E_TEX_TYPE::NORMAL:
		mat->mNorms.push_back(tmpTex);
		break;
	case E_TEX_TYPE::SPECULAR:
		mat->mSpecs.push_back(tmpTex);
		break;
	case E_TEX_TYPE::AMBIENT:
		mat->mAmbients.push_back(tmpTex);
		break;
	default:
		break;
	}
}
