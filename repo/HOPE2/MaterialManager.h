#ifndef MATERIAL_MANAGER_H
#define MATERIAL_MANAGER_H

#include "LogManager.h"
#include <string>
#include <vector>

enum class E_TEX_TYPE
{
	DIFFUSE,
	OPACITY,
	NORMAL,
	SPECULAR,
	AMBIENT
};

struct Material
{
	std::string mName;
	std::vector<unsigned int> mDiffs;
	std::vector<unsigned int> mOpacs;
	std::vector<unsigned int> mNorms;
	std::vector<unsigned int> mSpecs;
	std::vector<unsigned int> mAmbients;
};

class MaterialManager
{
public:
	static LogManager* mLogManager;
public:
	MaterialManager();
	~MaterialManager();
private:
	std::vector<Material*> mMaterialLibrary;

public:
	unsigned int addMaterial(Material* mat);
	void addTextureToMat(unsigned int matID, unsigned int texture, E_TEX_TYPE type);
	unsigned int getMaterialID(std::string name);
	unsigned int loadImage(const char* file);
};
#endif

