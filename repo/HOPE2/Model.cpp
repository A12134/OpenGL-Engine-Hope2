#include "Model.h"

MeshManager* Model::mMeshManager;
MaterialManager* Model::mMaterialMananger;

Model::Model(MeshNode* root)
{
	mRootNode = root;
	mCurrentNode = root;
}


Model::~Model()
{
}
