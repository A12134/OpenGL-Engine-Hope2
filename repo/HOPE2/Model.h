#ifndef MODEL_H
#define MODEL_H
#include "MeshNode.h"
#include "MeshManager.h"
#include "TextureManager.h"
#include "ShaderProgram.h"


class Model
{
public:
	static MeshManager* mMeshManager;
	static TextureManager* mTexManager;

private:
	MeshNode * mRootNode;
	MeshNode * mCurrentNode;
public:
	void render(ShaderProgram* sp, mat4 model, mat4 view, mat4 projection, MeshNode* node);
	Model();
	~Model();

	MeshNode* getRoot() { return mRootNode; }
	void setRoot(MeshNode* node) { mRootNode = node; }
};
#endif

