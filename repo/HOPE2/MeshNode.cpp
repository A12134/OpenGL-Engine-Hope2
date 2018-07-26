#include "MeshNode.h"



void MeshNode::addChild(MeshNode * child)
{
	child->setParent(this);
	this->mChildren.push_back(child);
}

MeshNode::MeshNode()
{
	mParent = nullptr;
}


MeshNode::~MeshNode()
{
}
