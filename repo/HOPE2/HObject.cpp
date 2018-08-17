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

void HObject::render(SimpleCamera* cam, std::vector<HMaterial*> mats)
{
	mat4 model = mat4(1);
	model = translate(model, mTrans.mPos);
	model = scale(model, mTrans.mScale);
	model = rotate(model, radians(mTrans.mRot), vec3(0.0f, 1.0f, 0.0f));
	for (unsigned int i = 0; i < mObject.size(); i++)
	{
		mObject.at(i).render(model, cam->getViewMatrix(), cam->getProjectionMatrix(), mats.at(i), sp, cam->getCamPos());
	}
}
