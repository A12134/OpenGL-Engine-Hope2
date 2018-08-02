#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
#include "SimpleCamera.h"
#include "LogManager.h"
#include "TextureManager.h"
#include <vector>
#include "Mesh.h"
#include <string>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "ShaderProgram.h"
#include "Model.h"

using namespace glm;

struct transformation
{
	transformation() {};
	transformation(vec3 _position, float _rotation, vec3 _scale) :
		position(_position),
		rotation(_rotation),
		scale(_scale)
	{};

	vec3 position;
	float rotation;
	vec3 scale;
};

class GameObject
{
public:
	static TextureManager* mTexManager;
	static LogManager* mLogManager;

protected:
	transformation mTransform;
	ShaderProgram* sp;
	Model* mMesh;

public:
	GameObject(transformation trans, ShaderProgram* sp);

	MeshNode* getModelRoot() { return mMesh->getRoot(); }

	~GameObject();
public:
	virtual void update(float deltaSeconds);
	virtual void render(SimpleCamera* cam);

};
#endif