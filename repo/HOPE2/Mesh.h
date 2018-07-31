#ifndef MESH_H
#define MESH_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "ShaderProgram.h"
#include "LogManager.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>
#include "TextureManager.h"

using namespace glm;
using namespace std;

struct Vertex 
{
	vec3 mPosition;
	vec3 mNormal;
	vec2 mTexCoords;
	vec3 mTangent;
	vec3 mBiTangent;
};

class Mesh
{
public:
	static LogManager* mLogManager;
private:
	vector<Vertex> mVertices;
	vector<unsigned int> mIndices;
	std::string mName;
	unsigned int VAO, VBO, EBO;
	bool setUniformSample;
public:
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices);
	~Mesh();
private:
	void initMesh();

public:
	std::string getName() { return mName; };
	void render(ShaderProgram* sp, mat4 model, mat4 view, mat4 projection, Material* mat);


};
#endif

