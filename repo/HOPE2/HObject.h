#ifndef H_OBJECT_H
#define H_OBJECT_H
#include "Resource.h"
#include "HMesh.h"
#include "HMaterial.h"
class HObject :
	public Resource
{
private:
	std::vector<HMesh> mObject;
	unsigned int mMaterialID;

public:
	HObject();
	~HObject();

	void pushBack(HMesh mesh);
};
#endif
