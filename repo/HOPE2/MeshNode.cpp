#include "MeshNode.h"



void MeshNode::addChild(MeshNode * child)
{
	child->setParent(this);
	this->mChildren.push_back(child);
}

MeshNode * MeshNode::addNewChild()
{
	this->mChildren.push_back(new MeshNode());
	this->mChildren.at(this->mChildren.size() - 1)->setParent(this);
	return this->mChildren.at(this->mChildren.size()-1);

}

MeshNode::MeshNode()
{
	mParent = nullptr;
}


MeshNode::~MeshNode()
{
}
