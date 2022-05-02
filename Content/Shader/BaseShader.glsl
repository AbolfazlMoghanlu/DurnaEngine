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
layout (location = 1) in vec4 VColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 V_Color;
out vec2 TexCoord;

void main()
{
	gl_Position =  Projection * View * Transform * vec4(aPos, WFactor);

	V_Color = VColor;
	TexCoord = aTexCoord;
}


#type fragment
#version 460 core

out vec4 FragColor;

in vec4 V_Color;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float time;

void main()
{
	//FragColor = V_Color;
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 1);
}