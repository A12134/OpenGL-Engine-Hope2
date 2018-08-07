#include "HMesh.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"


HMesh::HMesh()
{
}


HMesh::~HMesh()
{
}

void HMesh::render(glm::mat4 model, glm::mat4 view, glm::mat4 projection, HMaterial * mat, ShaderProgram* sp)
{
	sp->useThis();
	// load in textures
	for (unsigned int i = 0; i < 10; i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		unsigned int address = mat->getTextureSlot(i);
		if (address != 0xffffffffffffffff)
		{
			sp->setUniform1i(("slot" + std::to_string(i)).c_str(), i);
			glBindTexture(GL_TEXTURE_2D, address);
		}
	}

	// calculate tranformation matrix
	glm::mat4 transform = projection * view * model;
	sp->setUniformMatrix4x4fv("transformationMatrix", transform, GL_FALSE);

	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, this->mIndices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void HMesh::initMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, mVertices.size() * sizeof(vertex), &mVertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, mIndices.size() * sizeof(unsigned int), &mIndices.front(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mNormal));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(vertex), (void*)offsetof(vertex, mUV));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}
