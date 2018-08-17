#ifndef H_MESH_H
#define H_MESH_H
#include "Resource.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "HMaterial.h"
#include "ShaderProgram.h"

struct bone
{
	bone() :
		mBoneName("None"),
		mWeight(0.0f)
	{};
	std::string mBoneName;
	float mWeight;
};
struct vertex
{
	glm::vec3 mPos;
	glm::vec3 mNormal;
	glm::vec2 mUV;
	bone mBone1;
	bone mBone2;
	bone mBone3;
	bone mBone4;
};

class HMesh :
	public Resource
{
private:
	std::vector<vertex> mVertices;
	std::vector<unsigned int> mIndices;
	unsigned int mMaterialID;
	unsigned int EBO, VAO, VBO;

public:
	HMesh();
	~HMesh();

	void pushBack(vertex v) { mVertices.push_back(v); }
	void pushBack(unsigned int i) { mIndices.push_back(i); }
	void setMaterialID(unsigned int ID) { this->mMaterialID = ID; }

	vertex* getVertex(unsigned int ID) { return &mVertices.at(ID); }

	unsigned int getMaterialID() { return mMaterialID; }

	void render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, HMaterial* mat, ShaderProgram* sp, glm::vec3 camPos);

private:
	void initMesh();

	void loadInLight(ShaderProgram* sp);

	void loadInTexture(ShaderProgram* sp, HMaterial* mat);

};
#endif

