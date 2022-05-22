#type vertex
#version 460 core
uniform vec3 CameraPosition;
uniform vec3 CameraRotation;
uniform mat4 view;

uniform float WFactor;
uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

uniform float time;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 VNormal;

out vec4 V_Color;
out vec3 WorldPosition;
out vec2 TexCoord;
out vec3 WorldNormal;

void main()
{
	WorldPosition = (Transform * vec4(aPos, 1)).xyz;
	gl_Position =  Projection * View * vec4(WorldPosition, 1);

	TexCoord = aTexCoord;
	WorldNormal = normalize((Transform * vec4(VNormal, 0)).xyz);
}


#type fragment
#version 460 core

layout(location = 0) out vec3 FragPosition;
layout(location = 1) out vec4 FragColor;
layout(location = 2) out vec3 Normal;
layout(location = 3) out vec4 S_R_M_AO;


in vec3 WorldPosition;
in vec2 TexCoord;
in vec3 WorldNormal;

uniform sampler2D TextureAlbedo;
uniform sampler2D TextureNormal;
uniform sampler2D TextureMasks;


uniform mat4 Transform;
uniform float time;
uniform float Specular;

void main()
{
	vec4 Color = texture(TextureAlbedo, TexCoord * vec2(1, -1));
	vec3 TangentNormal = texture(TextureNormal, TexCoord * vec2(1, -1)).xyz;
	vec4 Masks = texture(TextureMasks, TexCoord * vec2(1, -1));

	TangentNormal = normalize(TangentNormal * 2 - 1);

	Color = vec4(pow(Color.xyz, vec3(2.2f)), 1);

	FragColor = Color;
	FragPosition = WorldPosition;
	//Normal = WorldNormal;
	Normal = TangentNormal * WorldNormal;
	S_R_M_AO = Masks;
}