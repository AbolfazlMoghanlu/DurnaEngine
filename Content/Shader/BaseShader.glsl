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
layout (location = 3) in vec3 vTangent;
layout (location = 4) in vec3 vBionormal;


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

uniform sampler2D texture1;
uniform sampler2D texture2;


uniform mat4 Transform;
uniform float time;
uniform float Specular;

void main()
{
	vec4 Color = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 1);

	FragColor = pow(Color, vec4(2.2f, 2.2f, 2.2f, 1.0f));
	FragPosition = WorldPosition;
	Normal = WorldNormal;
	S_R_M_AO = vec4(Specular, 0.0f, 0.0f, 0.0f);
}