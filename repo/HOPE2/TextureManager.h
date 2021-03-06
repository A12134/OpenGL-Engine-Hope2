#ifndef TEXTURE_MANAGER_H
#define TEXTURE_MANAGER_H
#include "LogManager.h"
#include <vector>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

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
	unsigned int skyBox_1;

public:
	TextureManager();
	~TextureManager();

	Material* createMaterial(std::string name);
	unsigned int getMaterialID(std::string name);

	std::vector<Texture>* getTextures(E_TEX_TYPE type, Material* mat);

	void loadSkyBox(std::vector<std::string> faces);
	unsigned int getSkyBox() { return skyBox_1; }
	Material* getMaterials(std::string matName);
	Material* getMaterialByID(unsigned int ID) { return &mMaterials.at(ID); }

	void loadImage(const char* filename, E_TEX_TYPE type, Material* mat);
};
#endif

