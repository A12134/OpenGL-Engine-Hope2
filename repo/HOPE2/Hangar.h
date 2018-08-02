#ifndef HANGER_H
#define HANGER_H
#include "GameObject.h"

class Hangar :
	public GameObject
{
public:
	Hangar(ShaderProgram* sp, transformation trans);
	~Hangar();
};
#endif

