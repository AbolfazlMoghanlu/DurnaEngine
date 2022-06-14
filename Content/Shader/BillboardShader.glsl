#type vertex
#version 460 core

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 WorldPosition;
out vec2 TexCoord;

uniform vec3 CameraLocation;
uniform float Time;
uniform float ObjectOrientation;

void main()
{
	WorldPosition = (Transform * vec4(aPos, 1)).xyz;

	vec2 CameraForwardVector = normalize((CameraLocation - WorldPosition).xy);
	vec3 PivotPoint = (Transform * vec4(0, 0, 0, 1)).xyz;


	WorldPosition -= PivotPoint;

	float CameraRotation = atan(CameraForwardVector.y, CameraForwardVector.x);

	float Delta = -ObjectOrientation * 3.14f / 180.0f;
	Delta += CameraRotation;

	Delta -= 3.14 / 2;

	vec3 WorldPosition = vec3(WorldPosition.x * cos(Delta) - WorldPosition.y * sin(Delta),
		WorldPosition.x * sin(Delta) + WorldPosition.y * cos(Delta), WorldPosition.z);

	WorldPosition += PivotPoint;

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