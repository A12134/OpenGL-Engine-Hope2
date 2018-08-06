#ifndef H_MESH_H
#define H_MESH_H
#include "Resource.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

struct bone
{
	int mBoneID;
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
public:
	HMesh();
	~HMesh();

	void pushBack(vertex v) { mVertices.push_back(v); }
	void pushBack(unsigned int i) { mIndices.push_back(i); }

private:
	void initMesh();

};
#endif

