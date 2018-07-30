#version 330 core

uniform sampler2D diffuseMap[10];
uniform sampler2D opacityMap[10];
uniform sampler2D normalMap[10];
uniform sampler2D specularMap[10];
uniform sampler2D amibentMap[10];

in vec2 texCoord;
//in vec3 debugPos;
out vec4 FragColor;
//in mat4 t;
void main()
{
	FragColor = texture(diffuseMap[0], texCoord);
}