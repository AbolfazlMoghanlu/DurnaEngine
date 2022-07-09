#type vertex
#version 460 core

uniform vec3 CameraPosition;

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

layout (location = 0) in vec3 aPos;

out vec2 ScreenAlignedUVs;

void main()
{
	vec3 WorldPosition = (Transform * vec4(aPos, 1)).xyz;
	gl_Position =  Projection * View * vec4(WorldPosition, 1);
    ScreenAlignedUVs = gl_Position.xy / gl_Position.w;
    ScreenAlignedUVs = ScreenAlignedUVs * 0.5f + 0.5f;
}


#type fragment
#version 460 core

in vec2 ScreenAlignedUVs;

layout(location = 5) out vec4 Lighting;
layout(location = 1) out vec4 a;

uniform sampler2D Buffer_Position;
uniform sampler2D Buffer_Color;
uniform sampler2D Buffer_Normal;
uniform sampler2D Buffer_Specular_Roughness_Metalic_AO;

uniform vec3 LightLocation;
uniform vec3 LightColor;
uniform float Attenuation;

void main()
{
	vec4 SceneColor = texture(Buffer_Color, ScreenAlignedUVs);
    vec3 Normal = texture(Buffer_Normal, ScreenAlignedUVs).xyz;
    vec3 WorldPosition = texture(Buffer_Position, ScreenAlignedUVs).xyz;
    vec4 S_R_M_AO = texture(Buffer_Specular_Roughness_Metalic_AO, ScreenAlignedUVs);

    float Specular   = S_R_M_AO.x;
    float Roughness  = S_R_M_AO.y;
    float Metallic    = S_R_M_AO.z;
    float AO         = S_R_M_AO.w;


    vec3 PixelPositionToLight = LightLocation - WorldPosition;
    float Distance = length(PixelPositionToLight);

    //Distance /= Attenuation; 
    //Distance = clamp(Distance, 0, 1);
    //Distance = 1 - Distance;

    //float Attenuation =  (Distance * Distance);

    Distance /= 1;

    float A = Distance / Attenuation;
    A = clamp(A, 0, 1);
    A = 1 - A;

    vec3 Radiance = LightColor * A;

    vec3 LightDir = normalize(PixelPositionToLight);
    float DiffuseLight = max(dot(LightDir, Normal), 0.0f);

	Lighting = vec4(Radiance, 1) * DiffuseLight;
	//Lighting = vec4(A);
    //a = vec4(LightColor, 1);
}