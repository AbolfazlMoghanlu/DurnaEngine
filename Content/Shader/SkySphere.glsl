#type vertex
#version 460 core

uniform float WFactor;
uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

uniform float time;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 VNormal;

out vec2 TexCoord;
out vec3 WorldNormal;

void main()
{
	TexCoord = aTexCoord;
	gl_Position =  Projection * View * Transform * vec4(aPos, 1);

	WorldNormal = normalize((Transform * vec4(VNormal, 0)).xyz);
}


#type fragment
#version 460 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec3 Normal;

in vec2 TexCoord;
in vec3 WorldNormal;

uniform sampler2D SkyTexture;
uniform float time;
uniform float SkyLightIntensity;
uniform mat4 Transform;

void main()
{
	vec4 SkySampled = pow(texture(SkyTexture, TexCoord), vec4(2.2));
	FragColor = SkySampled * SkyLightIntensity;

	Normal = WorldNormal;
}