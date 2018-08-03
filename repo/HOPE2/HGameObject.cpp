#include "HGameObject.h"

LogManager* HGameObject::mLogManager;


HGameObject::HGameObject(Transform _trans, ShaderProgram * sp)
{
	this -> mTrans = _trans;
	this->sp = sp;
	this->mModel = new Model();
}

HGameObject::~HGameObject()
{
}

void HGameObject::update(float deltaSconds)
{
}

void HGameObject::render(SimpleCamera * cam)
{
	mat4 model = mat4(1);
	model = translate(model, mTrans.mPos);
	model = scale(model, mTrans.mScale);
	model = rotate(model, radians(mTrans.mRot), vec3(0.0f, 1.0f, 0.0f));

	this->mModel->render(this->sp, model, cam->getViewMatrix(), cam->getProjectionMatrix(), this->mModel->getRoot());
}
