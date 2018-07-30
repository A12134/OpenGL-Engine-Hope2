#ifndef MESH_NODE_H
#define MESH_NODE_H
#include <vector>
class MeshNode
{
private:
	MeshNode * mParent;
	std::vector<MeshNode*> mChildren;
	std::vector<unsigned int> mMeshIDs;
	unsigned int mMaterialID;

public:

	// accessors and mutators
	//void setMeshID(unsigned int meshID) { mMeshID = meshID; }
	void setMaterialID(unsigned int materialID) { mMaterialID = mMaterialID; }
	void addMeshID(unsigned int meshID) { mMeshIDs.push_back(meshID); }
	//unsigned int getMeshID() { return mMeshID; }
	std::vector<unsigned int> getMeshIDs() { return mMeshIDs; }
	unsigned int getMaterialID() { return mMaterialID; }
	void addChild(MeshNode* child);
	MeshNode* addNewChild();
	void setParent(MeshNode* parent) { mParent = parent; }
	std::vector<MeshNode*> getChildren() { return mChildren; }
	MeshNode* getParent() { return mParent; }


	MeshNode();
	~MeshNode();
};
#endif

