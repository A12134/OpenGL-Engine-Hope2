#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord;

uniform mat4 transformationMatrix;

out vec3 Pos;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
	Pos = transformationMatrix * vec4(aPos, 1.0);;
	gl_Position = Pos;
	Normal = aNormal;
	TexCoord = aTexCoord;
}