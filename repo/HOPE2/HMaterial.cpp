#include "HMaterial.h"



HMaterial::HMaterial()
{
	this->textureSlot00 = textureSlot01 = textureSlot02 = textureSlot03 = textureSlot04
		= textureSlot05 = textureSlot06 = textureSlot07 = textureSlot08 = textureSlot09 = 0xffffffffffffffff;
}


HMaterial::~HMaterial()
{
}

void HMaterial::setTextureSlot(int num, unsigned int ID)
{
	switch (num) 
	{
	case 0:
		if (this->textureSlot00 == 0xffffffffffffffff)
		{
			this->textureSlot00 = ID;
		}
		break;
	case 1:
		if (this->textureSlot01 == 0xffffffffffffffff)
		{
			this->textureSlot01 = ID;
		}
		break;
	case 2:
		if (this->textureSlot02 == 0xffffffffffffffff)
		{
			this->textureSlot02 = ID;
		}
		break;
	case 3:
		if (this->textureSlot03 == 0xffffffffffffffff)
		{
			this->textureSlot03 = ID;
		}
		break;
	case 4:
		if (this->textureSlot04 == 0xffffffffffffffff)
		{
			this->textureSlot04 = ID;
		}
		break;
	case 5:
		if (this->textureSlot05 == 0xffffffffffffffff)
		{
			this->textureSlot05 = ID;
		}
		break;
	case 6:
		if (this->textureSlot06 == 0xffffffffffffffff)
		{
			this->textureSlot06 = ID;
		}
		break;
	case 7:
		if (this->textureSlot07 == 0xffffffffffffffff)
		{
			this->textureSlot07 = ID;
		}
		break;
	case 8:
		if (this->textureSlot08 == 0xffffffffffffffff)
		{
			this->textureSlot08 = ID;
		}
		break;
	case 9:
		if (this->textureSlot09 == 0xffffffffffffffff)
		{
			this->textureSlot09 = ID;
		}
		break;
	default:
		// slot does not exist;
		return;
		break;
	}
}
