#ifndef H_TEXTURE_H
#define H_TEXTURE_H
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Resource.h"
#include <string>
#include <vector>

class HTexture :
	public Resource
{
private:
	unsigned int TexID;
	std::string textureName;
public:
	HTexture();
	~HTexture();

	void setTexID(unsigned int ID) { TexID = ID; }
	void setTextureName(std::string name) { textureName = name; }

	std::string getTexName() { return textureName; }
	unsigned int* getTexID() { return &TexID; }

	/*Using glTexImage2D to assign texture after this function is called.*/
	void createNew2DTexture();
	/*Using glTexImage2D to assign texture after this function is called, required 6 textures*/
	void createNewCubeTexture();
};
#endif