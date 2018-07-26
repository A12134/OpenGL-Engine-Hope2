#ifndef MODEL_H
#define MODEL_H
#include "MeshNode.h"
#include "MeshManager.h"
#include "MaterialManager.h"

class Model
{
public:
	static MeshManager* mMeshManager;
	static MaterialManager* mMaterialMananger;

private:
	MeshNode * mRootNode;
	MeshNode * mCurrentNode;
public:
	Model(MeshNode* root);
	~Model();
};
#endif

