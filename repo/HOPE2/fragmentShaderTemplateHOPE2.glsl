#version 330 core

uniform vec3 cameraPos;

// texture slots
uniform sampler2D slot0;
uniform sampler2D slot1;
uniform sampler2D slot2;
uniform sampler2D slot3;
uniform sampler2D slot4;
uniform sampler2D slot5;
uniform sampler2D slot6;
uniform sampler2D slot7;
uniform sampler2D slot8;
uniform sampler2D slot9;
// light struct
struct DLight
{
	vec3 Direction;
	vec3 Color;
	float Intensive;
};

struct PLight
{
	vec3 Position;
	vec3 Color;
	float Intensive;
	vec3 Attenuation;
};

// maximum 4 directional light
uniform DLight dLight[3];

// maximum 63 point light
uniform PLight pLight[63];

in vec3 Pos;
in vec3 Normal;
in vec2 TexCoord;

// calcuate the directional light
void directionalLightCalculation(DLight light)
{
	vec3 lightDir = normalize(-light.Direction);
	// diffuse
	float diff = max(dot(Normal, lightDir), 0.0);
	// specular
	
}

// calculate the point light
void pointLightCalculation(PLight light)
{

}

void main()
{
	for(int i = 0; i < 4; i++)
	{
		directionalLightCalculation(dLight[i]);
	}

	for(int i = 0; i < 64; i++)
	{
		pointLightCalculation(pLight[i]);
	}
}

