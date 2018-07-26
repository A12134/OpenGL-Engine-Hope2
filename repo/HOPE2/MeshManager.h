#ifndef MESH_MANAGER_H
#define MESH_MANAGER_H
#include "LogManager.h"
#include "Mesh.h"
#include <vector>
#include "ShaderProgram.h"

class MeshManager
{
public:
	static LogManager* mLogManager;
private:
	std::vector<Mesh*> mMeshLibrary;

public:
	unsigned int addMesh(Mesh* newMesh);
	unsigned int getMeshID(std::string meshName);
	void renderMesh(unsigned int ID, ShaderProgram* sp, mat4 model, mat4 view, mat4 projection, unsigned int MaterialID);
	MeshManager();
	~MeshManager();
};
#endif

