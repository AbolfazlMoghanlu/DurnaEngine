#type vertex
#version 460 core

uniform float WFactor;
uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

uniform float time;

layout (location = 0) in vec3 aPos;
//layout (location = 1) in vec2 aTTT;
layout (location = 2) in vec3 VNormal;
layout (location = 3) in vec3 vTangent;
layout (location = 4) in vec3 vBionormal;

out vec3 WorldPosition;
out vec3 TexCoord;
out vec3 WorldNormal;

void main()
{
	WorldPosition = (Transform * vec4(aPos, 1)).xyz;
	gl_Position =  Projection * View * vec4(WorldPosition, 1);

	TexCoord = vec3(aPos.x, aPos.z, aPos.y);

	WorldNormal = normalize((Transform * vec4(VNormal, 0)).xyz);
}


#type fragment
#version 460 core

layout(location = 0) out vec3 FragPosition;
layout(location = 1) out vec4 FragColor;
layout(location = 2) out vec3 Normal;
layout(location = 3) out vec4 S_R_M_AO;
layout(location = 4) out uint FragShadingModel;

in vec3 WorldPosition;
in vec3 WorldNormal;
in vec3 TexCoord;

uniform int ShadingModel;

uniform samplerCube SkyCubemap;

uniform float time;
uniform vec3 OverallColor;
uniform mat4 Transform;

void main()
{
	vec4 SkySampled = texture(SkyCubemap, TexCoord);
	FragColor = pow(SkySampled, vec4(2.2f)) * vec4(OverallColor, 1.0f);
	FragPosition = WorldPosition;

	Normal = WorldNormal;
	S_R_M_AO = vec4(0);
	FragShadingModel = ShadingModel;
}