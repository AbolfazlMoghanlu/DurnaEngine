#type vertex
#version 460 core

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 ActorLocation;
uniform vec3 CameraLocation;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 TexCoord;
layout (location = 2) in vec3 VNormal;
layout (location = 3) in vec3 vTangent;
layout (location = 4) in vec3 vBionormal;

out vec3 WorldPosition;
out vec2 UVs;
out vec3 WorldNormal;

void main()
{
	vec3 Distance = CameraLocation - ActorLocation;
	float len = sqrt(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);

	WorldPosition = (Transform * vec4(aPos * len, 1)).xyz;
	gl_Position =  Projection * View * vec4(WorldPosition, 1);
	
	UVs = TexCoord;
	WorldNormal = normalize((Transform * vec4(VNormal, 0)).xyz);
}


#type fragment
#version 460 core

layout(location = 0) out vec3 FragPosition;
layout(location = 1) out vec4 FragColor;
layout(location = 2) out vec3 Normal;
layout(location = 3) out vec4 S_R_M_AO;

in vec3 WorldPosition;
in vec3 WorldNormal;
in vec2 UVs;

uniform sampler2D BaseColor;

void main()
{
	FragColor = texture(BaseColor, vec2(UVs.x, UVs.y * -1));

	FragPosition = WorldPosition;
	Normal = WorldNormal;
	S_R_M_AO = vec4(0);
}