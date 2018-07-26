#ifndef MESH_NODE_H
#define MESH_NODE_H
#include <vector>
class MeshNode
{
private:
	MeshNode * mParent;
	std::vector<MeshNode*> mChildren;
	unsigned int mMeshID;
	unsigned int mMaterialID;

public:

	// accessors and mutators
	void setMeshID(unsigned int meshID) { mMeshID = meshID; }
	void setMaterialID(unsigned int materialID) { mMaterialID = mMaterialID; }
	unsigned int getMeshID() { return mMeshID; }
	unsigned int getMaterialID() { return mMaterialID; }
	void addChild(MeshNode* child);
	void setParent(MeshNode* parent) { mParent = parent; }
	std::vector<MeshNode*> getChildren() { return mChildren; }
	MeshNode* getParent() { return mParent; }


	MeshNode();
	~MeshNode();
};
#endif

