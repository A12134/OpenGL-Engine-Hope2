#include "Model.h"

MeshManager* Model::mMeshManager;
TextureManager* Model::mTexManager;

void Model::render(ShaderProgram* sp, mat4 model, mat4 view, mat4 projection, MeshNode* node)
{
	for (unsigned int i = 0; i < node->getMeshIDs().size(); i++)
	{
		mMeshManager->renderMesh(node->getMeshIDs().at(i), sp, model, view, projection, node->getMaterialID());
	}
	
	for (unsigned int  i = 0; i < node->getChildren().size(); i++)
	{
		render(sp, model, view, projection, node->getChildren().at(i));
	}
}

Model::Model()
{
	mRootNode = new MeshNode();
}


Model::~Model()
{
}
