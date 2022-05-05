#type vertex
#version 460 core

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 ActorLocation;
uniform vec3 CameraLocation;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 TexCoord;

out vec2 UVs;

void main()
{
	vec3 Distance = CameraLocation - ActorLocation;
	float len = sqrt(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);
	gl_Position =  Projection * View * Transform * vec4(aPos * len, 1);

	UVs = TexCoord;
}


#type fragment
#version 460 core

in vec2 UVs;
out vec4 FragColor;

uniform sampler2D BaseColor;

void main()
{
	FragColor = texture(BaseColor, vec2(UVs.x, UVs.y * -1));
}