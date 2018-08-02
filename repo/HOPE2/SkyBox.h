#ifndef SKY_BOX_H
#define SKY_BOX_H
#include "Mesh.h"
#include "TextureManager.h"
#include <vector>
#include <string>
#include "ShaderProgram.h"
class SkyBox
{
public:
	static TextureManager* mTexManager;
private:
	static float skyboxVertices[];
	static std::vector<std::string> imageFaces;

private:
	unsigned int skyboxVAO, skyboxVBO;
	ShaderProgram* skyboxSp;

public:
	SkyBox(ShaderProgram* skyboxSp);
	~SkyBox();

	void render(mat4 viewMatrix, mat4 projectionMatrix);
};
#endif

