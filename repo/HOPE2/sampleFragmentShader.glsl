#version 330 core

uniform sampler2D diffuseMap;
uniform sampler2D opacityMap;
uniform sampler2D normalMap;
uniform sampler2D specularMap;
uniform sampler2D amibentMap;

in vec2 texCoord;
//in vec3 debugPos;
out vec4 FragColor;
//in mat4 t;
void main()
{
	FragColor = texture(diffuseMap, texCoord);
}