#type vertex
#version 460 core

uniform float WFactor;
uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 TexCoord;

out vec2 UVs;

void main()
{
	UVs = TexCoord;
	gl_Position =  Projection * View * Transform * vec4(aPos, WFactor);
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