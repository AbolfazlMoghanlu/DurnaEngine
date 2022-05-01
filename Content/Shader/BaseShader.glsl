#type vertex
#version 460 core
uniform vec3 CameraPosition;
uniform vec3 CameraRotation;
uniform mat4 view;
uniform mat4 Translation;
uniform mat4 Rotation;
uniform mat4 Scale;
uniform mat4 Transform;
uniform mat4 Projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 VColor;
layout (location = 2) in vec2 aTexCoord;

out vec4 V_Color;
out vec2 TexCoord;

void main()
{
	//gl_Position = view * vec4(aPos, 1.0f);	
	//gl_Position = vec4(aPos, 1.0f);
	
	//gl_Position = Translation * vec4(aPos, 1.0f);
	//gl_Position = Rotation * vec4(aPos, 1.0f);
	//gl_Position = Translation * Rotation * vec4(aPos, 1.0f);
	//gl_Position = Translation * Rotation * Scale * vec4(aPos, 1.0f);
//	gl_Position =  vec4(0, 0, 2, 0) + vec4(aPos, 1.0f);
	gl_Position =  Projection *  Transform * vec4(aPos, 20.0f);
//	gl_Position = Projection * Transform * vec4(aPos, 1.0f);

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
	FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), abs(sin(time)));
	//FragColor = vec4(sin(time));
}