#ifndef RESOURCE_H
#define RESOURCE_H
class Resource
{
private:
	long RID;
	int type;
	/*
		-The type of this resource
		-	0: Mesh
		-	1: Object
		-	2: Texture
		-	3: Material
	*/
public:
	Resource();
	~Resource();

	void setRID(long _RID) { RID = _RID; };
	long getRID() { return RID; };
	void setType(int _type) { type = _type; };
	int getType() { return type; }
};
#endif

