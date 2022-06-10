#type vertex
#version 460 core

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

layout (location = 0) in vec3 aPos;

out vec3 WorldPosition;

void main()
{
	WorldPosition = (Transform * vec4(aPos, 1)).xyz;
	gl_Position =  Projection * View * vec4(WorldPosition, 1);
}


#type fragment
#version 460 core

layout(location = 0) out vec3 FragPosition;
layout(location = 1) out vec4 FragColor;
layout(location = 2) out vec3 Normal;
layout(location = 3) out vec4 S_R_M_AO;

in vec3 WorldPosition;

void main()
{
	FragColor = vec4(0.2f, 0.45f, 0.85f, 1.0f);

	FragPosition = WorldPosition;
	Normal = vec3(0.0f, 0.0f, 1.0f);
	S_R_M_AO = vec4(0);
}