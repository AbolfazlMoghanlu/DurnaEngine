#type vertex
#version 460 core

uniform float WFactor;
uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

uniform float time;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 VColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 V_Color;
out vec2 TexCoord;

void main()
{
	TexCoord = aTexCoord;
	gl_Position =  Projection * View * Transform * vec4(aPos, WFactor);
}


#type fragment
#version 460 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D SkyTexture;
uniform float time;

void main()
{
	vec4 SkySampled = pow(texture(SkyTexture, TexCoord), vec4(2.2));
	FragColor = SkySampled;
}