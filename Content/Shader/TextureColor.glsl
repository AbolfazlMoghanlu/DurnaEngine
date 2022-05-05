#type vertex
#version 460 core

uniform float WFactor;
uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 TexCoord;

out vec2 UVs;
out vec3 VertexPosition;

void main()
{
	gl_Position =  Projection * View * Transform * vec4(aPos, WFactor);

	UVs = TexCoord;
	VertexPosition = (Transform * vec4(aPos, 1)).xyz;
}


#type fragment
#version 460 core

in vec2 UVs;
in vec3 VertexPosition;
out vec4 FragColor;

uniform sampler2D BaseColor;
uniform vec3 CameraLocation;

void main()
{
	vec3 Distance = (CameraLocation * 1 - VertexPosition);

	float len = sqrt(Distance.x * Distance.x + Distance.y * Distance.y + Distance.z * Distance.z);

	//FragColor = texture(BaseColor, vec2(UVs.x, UVs.y * -1)) * a * .01;

	float a = len < 1 ? 1 : 0;

	FragColor = vec4(vec3(a), 1);

	//FragColor = vec4(VertexPosition * .1, 1);
}