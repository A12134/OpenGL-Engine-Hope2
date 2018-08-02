#include "SkyBox.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

TextureManager* SkyBox::mTexManager;

float SkyBox::skyboxVertices[] = 
{
	// positions          
	-1.0f,  1.0f, -1.0f,
	-1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f, -1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,

	-1.0f, -1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f, -1.0f,  1.0f,
	-1.0f, -1.0f,  1.0f,

	-1.0f,  1.0f, -1.0f,
	1.0f,  1.0f, -1.0f,
	1.0f,  1.0f,  1.0f,
	1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f,  1.0f,
	-1.0f,  1.0f, -1.0f,

	-1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f, -1.0f,
	1.0f, -1.0f, -1.0f,
	-1.0f, -1.0f,  1.0f,
	1.0f, -1.0f,  1.0f
};

std::vector<std::string> SkyBox::imageFaces =
{
	"assets/skybox//right.jpg",
	"assets/skybox//left.jpg",
	"assets/skybox//top.jpg",
	"assets/skybox//bottom.jpg",
	"assets/skybox//front.jpg",
	"assets/skybox//back.jpg"
};

SkyBox::SkyBox(ShaderProgram * skyboxSp)
{

	// skybox VAO
	glGenVertexArrays(1, &skyboxVAO);
	glGenBuffers(1, &skyboxVBO);
	glBindVertexArray(skyboxVAO);
	glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), &skyboxVertices, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

	mTexManager->loadSkyBox(this->imageFaces);

	this->skyboxSp = skyboxSp;

	skyboxSp->useThis();
	skyboxSp->setUniform1i("skybox", 0);
}

SkyBox::~SkyBox()
{
}

void SkyBox::render(mat4 viewMatrix, mat4 projectionMatrix)
{
	glDepthMask(GL_FALSE);
	skyboxSp->useThis();
	mat4 transform = projectionMatrix*mat4(mat3(viewMatrix));
	skyboxSp->setUniformMatrix4x4fv("transform", transform, GL_FALSE);

	glBindVertexArray(skyboxVAO);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, mTexManager->getSkyBox());
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
	glDepthMask(GL_TRUE);
}
