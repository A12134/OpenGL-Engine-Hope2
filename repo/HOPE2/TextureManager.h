/*TODO: 
	- simplify enum classes
	- figure out the relationships between materials and textures
	- write the method to access the texture from the material efficiently
*/

#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "LogManager.h"
#include <vector>

enum class TEX_PARA 
{
	E_WRAP_REPEAT,
	E_WRAP_MIRRORED_REPEAT,
	E_WRAP_CLAMP_TO_EDGE,
	E_WRAP_CLAMP_TO_BORDER,
	E_FILTER_LINEAR,
	E_FILTER_NEAREST,
	E_FILTER_NEAREST_MIPMAP_NEAREST,
	E_FILTER_LINEAR_MIPMAP_NEAREST,
	E_FILTER_NEAREST_MIPMAP_LINEAR,
	E_FILTER_LINEAR_MIPMAP_LINEAR
};

enum class E_TEX_TYPE 
{
	DIFFUSE,
	OPACITY,
	NORMAL,
	SPECULAR,
	AMBIENT
};

struct Texture 
{
	unsigned int mTextureID;
	std::string mTextureName;
};

struct Material 
{
	std::string mName;
	std::vector<Texture> mDiffs;
	std::vector<Texture> mOpacs;
	std::vector<Texture> mNorms;
	std::vector<Texture> mSpecs;
	std::vector<Texture> mAmbients;
};

class TextureManager
{
private:
	std::vector<Material> mMaterials;
public:
	static LogManager* mLogManager;
public:
	TextureManager();
	~TextureManager();
	
	/*
	@param:
	num: an integer
	1: diffuse maps
	2: opacity maps
	3: normal maps
	4: specular maps
	5: ambient maps
	*/
	void addToMaterial(Material* mat, Texture tex, int num);

	/*
	@param:	
		num: an integer
		1: diffuse maps
		2: opacity maps
		3: normal maps
		4: specular maps
		5: ambient maps
	*/
	std::vector<Texture>* getTextures(int num, Material* mat);

	Material* getMaterials(std::string matName);

	void loadImage(const char* filename, E_TEX_TYPE type);
};
#endif

