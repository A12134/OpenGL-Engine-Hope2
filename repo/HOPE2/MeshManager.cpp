#include "MeshManager.h"

LogManager* MeshManager::mLogManager;

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
	this->mMeshLibrary.at(ID)->render(sp, model, view, projection, nullptr);	// Material ID
}

MeshManager::MeshManager()
{
}

MeshManager::~MeshManager()
{
}
