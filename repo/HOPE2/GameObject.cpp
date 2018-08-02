#include "GameObject.h"
#include "SimpleCamera.h"

LogManager* GameObject::mLogManager;
TextureManager* GameObject::mTexManager;

GameObject::GameObject(transformation trans, ShaderProgram * sp)
{
	this->mMesh = new Model();
	this->sp = sp;
}

GameObject::~GameObject()
{
}




void GameObject::update(float deltaSeconds)
{
}

void GameObject::render(SimpleCamera * cam)
{
	mat4 model = mat4(1.0f);
	model = translate(model, mTransform.position);
	model = scale(model, mTransform.scale);
	model = rotate(model, radians(mTransform.rotation), vec3(0.0f, 1.0f, 0.0f));

	this->mMesh->render(sp, model, cam->getViewMatrix(), cam->getProjectionMatrix(), mMesh->getRoot());
}
