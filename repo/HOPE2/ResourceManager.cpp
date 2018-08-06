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

long ResourceManager::GenerateRID(std::string fileName)
{
	long hashVal = 3;
	for (int i = 0; i < fileName.length(); i++)
	{
		hashVal = hashVal * 7 + fileName[i];
	}
	return hashVal;
}
