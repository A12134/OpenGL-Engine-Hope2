#ifndef H_MATERIAL_H
#define H_MATERIAL_H
#include "Resource.h"
class HMaterial :
	public Resource
{
private:
	unsigned int textureSlot00;
	unsigned int textureSlot01;
	unsigned int textureSlot02;
	unsigned int textureSlot03;
	unsigned int textureSlot04;
	unsigned int textureSlot05;
	unsigned int textureSlot06;
	unsigned int textureSlot07;
	unsigned int textureSlot08;
	unsigned int textureSlot09;
public:
	HMaterial();
	~HMaterial();

	void setTextureSlot(int num, unsigned int ID);

	// @param: slot num: 0-9
	// @return: the address of the texture
	unsigned int getTextureSlot(int num);
};
#endif

