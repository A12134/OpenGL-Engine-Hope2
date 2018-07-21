#include "Mesh.h"

LogManager* Mesh::mLogManager;

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices)
{
	this->mVertices = vertices;
	this->mIndices = indices;
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

	mat4 matrices = projection * view * model;
	sp->setUniformMatrix4x4fv("transformation", matrices, GL_FALSE);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	// set back to default
	glActiveTexture(GL_TEXTURE0);

}
