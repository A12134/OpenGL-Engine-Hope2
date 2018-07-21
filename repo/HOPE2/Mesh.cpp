#include "Mesh.h"

LogManager* Mesh::mLogManager;


Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices)
{
	//this->mVertices = vertices;
	//this->mIndices = indices;

	Vertex v1;
	v1.mPosition = vec3(0.5f, 0.5f, 0.0f);
	v1.mNormal = vec3(1);
	v1.mBiTangent = vec3(1);
	v1.mTangent = vec3(1);
	v1.mTexCoords = vec2(1);
	Vertex v2;
	v2.mPosition = vec3(0.5f, -0.5f, 0.0f);
	v2.mNormal = vec3(1);
	v2.mBiTangent = vec3(1);
	v2.mTangent = vec3(1);
	v2.mTexCoords = vec2(1);
	Vertex v3;
	v3.mPosition = vec3(-0.5f, -0.5f, 0.0f);
	v3.mNormal = vec3(1);
	v3.mBiTangent = vec3(1);
	v3.mTangent = vec3(1);
	v3.mTexCoords = vec2(1);
	Vertex v4;
	v4.mPosition = vec3(-0.5f, 0.5f, 0.0f);
	v4.mNormal = vec3(1);
	v4.mBiTangent = vec3(1);
	v4.mTangent = vec3(1);
	v4.mTexCoords = vec2(1);

	this->mVertices.push_back(v1);
	this->mVertices.push_back(v2);
	this->mVertices.push_back(v3);
	this->mVertices.push_back(v4);

	this->mIndices.push_back(0);
	this->mIndices.push_back(1);
	this->mIndices.push_back(3);
	this->mIndices.push_back(1);
	this->mIndices.push_back(2);
	this->mIndices.push_back(3);

	initMesh();
}

Mesh::~Mesh()
{
}

void Mesh::initMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(Vertex), &mVertices.front(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices.front(), GL_STATIC_DRAW);

	// vertex position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	glEnableVertexAttribArray(0);
	// vertex normal
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mNormal));
	glEnableVertexAttribArray(1);
	// vertex texCoord
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mTexCoords));
	glEnableVertexAttribArray(2);
	// vertex tangent
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mTangent));
	glEnableVertexAttribArray(3);
	// vertex biTangent
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, mBiTangent));
	glEnableVertexAttribArray(4);

	glBindVertexArray(0);
}

void Mesh::render(ShaderProgram * sp, mat4 model, mat4 view, mat4 projection, Material* mat)
{
	sp->useThis();
	unsigned int texCount = 0;
	unsigned int texArray[10];
	// load diffuse
	for (unsigned int i = 0; i < 10; i++)
	{
		if (i < mat->mDiffs.size())
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			glBindTexture(GL_TEXTURE_2D, mat->mDiffs.at(i).mTextureID);
			texCount++;
			texArray[i] = texCount;
		}
		else
		{
			texArray[i] = 999;
		}
	}
	sp->setUniform1uiv("diffuseMap", 10, texArray);
	// load normal
	for (unsigned int i = 0; i < 10; i++)
	{
		if (i < mat->mNorms.size())
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			glBindTexture(GL_TEXTURE_2D, mat->mNorms.at(i).mTextureID);
			texCount++;
			texArray[i] = texCount;
		}
		else
		{
			texArray[i] = 999;
		}
	}
	sp->setUniform1uiv("normalMap", 10, texArray);
	// load opacity
	for (unsigned int i = 0; i < 10; i++)
	{
		if (i < mat->mOpacs.size())
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			glBindTexture(GL_TEXTURE_2D, mat->mOpacs.at(i).mTextureID);
			texCount++;
			texArray[i] = texCount;
		}
		else
		{
			texArray[i] = 999;
		}
	}
	sp->setUniform1uiv("opacityMap", 10, texArray);
	// load ambient
	for (unsigned int i = 0; i < 10; i++)
	{
		if (i < mat->mAmbients.size())
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			glBindTexture(GL_TEXTURE_2D, mat->mAmbients.at(i).mTextureID);
			texCount++;
			texArray[i] = texCount;
		}
		else
		{
			texArray[i] = 999;
		}
	}
	sp->setUniform1uiv("ambientMap", 10, texArray);
	// load specular
	for (unsigned int i = 0; i < 10; i++)
	{
		if (i < mat->mSpecs.size())
		{
			glActiveTexture(GL_TEXTURE0 + texCount);
			glBindTexture(GL_TEXTURE_2D, mat->mSpecs.at(i).mTextureID);
			texCount++;
			texArray[i] = texCount;
		}
		else
		{
			texArray[i] = 999;
		}
	}
	sp->setUniform1uiv("specularMap", 10, texArray);

	mat4 matrices =  model;
	//sp->setUniformMatrix4x4fv("transform", matrices, GL_FALSE);
	unsigned int transformationLoc = glGetUniformLocation(sp->getID(), "transform");
	glUniformMatrix4fv(transformationLoc, 1, GL_FALSE, value_ptr(matrices));

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// set back to default
	glActiveTexture(GL_TEXTURE0);

}
