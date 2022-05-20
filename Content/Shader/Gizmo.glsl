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

out vec2 UVs;
out vec3 WorldNormal;

void main()
{
	vec3 Distance = CameraLocation - ActorLocation;
	float len = sqrt(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);
	gl_Position =  Projection * View * Transform * vec4(aPos * len, 1);

	UVs = TexCoord;
	WorldNormal = normalize((Transform * vec4(VNormal, 0)).xyz);
}


#type fragment
#version 460 core

layout(location = 0) out vec4 FragColor;
layout(location = 1) out vec3 Normal;

in vec3 WorldNormal;
in vec2 UVs;

uniform sampler2D BaseColor;

void main()
{
	FragColor = texture(BaseColor, vec2(UVs.x, UVs.y * -1));

	Normal = WorldNormal;
}