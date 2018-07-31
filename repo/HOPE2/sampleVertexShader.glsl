#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBitangent;

uniform mat4 transform;
out vec2 texCoord;
//out vec3 debugPos;
//out mat4 t;

void main()
{
	gl_Position = transform * vec4(aPos.x,aPos.y, aPos.z, 1.0);
	texCoord = aTexCoord;
}