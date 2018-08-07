#ifndef H_OBJECT_H
#define H_OBJECT_H
#include "Resource.h"
#include "HMesh.h"
#include "HMaterial.h"
#include "SimpleCamera.h"
#include "ShaderProgram.h"

using namespace glm;
struct Transform
{
	Transform() {};
	Transform(vec3 _pos, float _rot, vec3 _scale) :
		mPos(_pos),
		mRot(_rot),
		mScale(_scale)
	{};

	vec3 mPos;
	float mRot;
	vec3 mScale;
};
class HObject :
	public Resource
{
private:
	std::vector<HMesh> mObject;
	Transform mTrans;
	std::vector<unsigned int> mMaterialsID;
	ShaderProgram* sp;

public:
	HObject();
	~HObject();

	void pushBack(HMesh mesh);

	void pushBack(unsigned int id) { mMaterialsID.push_back(id); };

	void render(SimpleCamera* cam, std::vector<HMaterial*> mats);

	unsigned int getMeshNum() { return mObject.size(); }

	unsigned int getMatAtMeshAt(unsigned int index) { return mObject.at(index).getMaterialID(); }
	
	unsigned int getMatNum() { return mMaterialsID.size(); }

	unsigned int getMatAtObjectAtIndex(unsigned int index) { return mMaterialsID.at(index); }
};
#endif
