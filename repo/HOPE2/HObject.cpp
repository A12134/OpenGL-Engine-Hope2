#include "HObject.h"



HObject::HObject()
{
}


HObject::~HObject()
{
}

void HObject::pushBack(HMesh mesh)
{
	mObject.push_back(mesh);
}
