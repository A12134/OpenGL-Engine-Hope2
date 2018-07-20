#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H
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
#include "BaseCamera.h"
#include "ShaderProgram.h"

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

private:
	std::vector<Mesh *> mMeshes;
	Material* mMaterial;
	std::vector<Texture *> mTexes;

public:
	GameObject();
	GameObject(std::string meshFile, Material* mat, transformation trans, ShaderProgram* sp);
	// GameObject(model, texture)
	GameObject(std::string meshFile, transformation trans, ShaderProgram* sp);
	// GameObject(model)	// obj file cames with texture
	~GameObject();

private:
	void loadModel(std::string fileName);
	void processNode(aiNode * node, const aiScene * scene, std::string fileName, std::string directory);
	Mesh* processMesh(aiMesh * mesh, const aiScene * scene, std::string fileName, std::string directory);

public:
	virtual void update(float deltaSeconds) = 0;
	virtual void render(SimpleCamera* cam);

};
#endif