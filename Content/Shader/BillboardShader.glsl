#type vertex
#version 460 core

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 WorldPosition;
out vec2 TexCoord;

uniform vec3 CameraForwardVector;

void main()
{
	//float Delta = atan(CameraForwardVector.y, CameraForwardVector.x);

	//vec3 RotatedPosition = vec3(aPos.x * cos(Delta) - aPos.y * sin(Delta) , aPos.x * sin(Delta) + aPos.y * cos(Delta), aPos.z);
	//vec3 RotatedPosition = vec3(aPos.x, aPos.y * cos(Delta) - aPos.z * sin(Delta), aPos.y * sin(Delta) + aPos.z * cos(Delta));
	//vec3 RotatedPosition = vec3(aPos.x, aPos.y * cos(Delta) - aPos.z * sin(Delta), aPos.y * sin(Delta) + aPos.z * cos(Delta));

	WorldPosition = (Transform * vec4(aPos, 1)).xyz;
	gl_Position =  Projection * View * vec4(WorldPosition, 1);

	TexCoord = aTexCoord;
}


#type fragment
#version 460 core

layout(location = 0) out vec3 FragPosition;
layout(location = 1) out vec4 FragColor;
layout(location = 4) out uint FragShadingModel;


in vec3 WorldPosition;
in vec2 TexCoord;

uniform sampler2D SpriteTexture;
uniform int ShadingModel;

void main()
{
	FragColor = texture(SpriteTexture, TexCoord);
	FragPosition = WorldPosition;
	FragShadingModel = ShadingModel;
}