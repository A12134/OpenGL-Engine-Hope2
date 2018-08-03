#ifndef H_GAME_OBJECT_H
#define H_GAME_OBJECT_H

#include "Model.h"
#include <glm/glm.hpp>
#include "SimpleCamera.h"
#include "LogManager.h"
#include "ShaderProgram.h"

struct Transform 
{
	Transform() {};
	Transform(vec3 _pos, float _rot, vec3 _scale):
		mPos(_pos),
		mRot(_rot),
		mScale(_scale)
	{};

	vec3 mPos;
	float mRot;
	vec3 mScale;
};
class HGameObject
{
public: 
	static LogManager* mLogManager;

protected:
	Model * mModel;
	Transform mTrans;
	ShaderProgram* sp;

public:
	HGameObject(Transform _trans, ShaderProgram* sp);
	~HGameObject();

	void assignModel(MeshNode* node) { this->mModel->setRoot(node); }
	MeshNode* getModelRoot() { return this->mModel->getRoot(); }
	virtual void update(float deltaSconds);
	void render(SimpleCamera* cam);
};
#endif

