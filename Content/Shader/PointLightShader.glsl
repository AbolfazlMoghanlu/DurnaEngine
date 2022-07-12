#type vertex
#version 460 core

uniform vec3 CameraPosition;

uniform mat4 Transform;
uniform mat4 View;
uniform mat4 Projection;

layout (location = 0) in vec3 aPos;
out vec3 ScreenSpaceTransform;

void main()
{
	vec3 WorldPosition = (Transform * vec4(aPos, 1)).xyz;
	gl_Position =  Projection * View * vec4(WorldPosition, 1);
    ScreenSpaceTransform = gl_Position.xyw;
}


#type fragment
#version 460 core

in vec3 ScreenSpaceTransform;

layout(location = 5) out vec4 Lighting;

uniform sampler2D Buffer_Position;
uniform sampler2D Buffer_Color;
uniform sampler2D Buffer_Normal;
uniform sampler2D Buffer_Specular_Roughness_Metalic_AO;

uniform vec3 LightLocation;
uniform vec3 LightColor;
uniform float InvRadius;

uniform vec3 CameraLocation;

const float PI = 3.14159265359;


float DistributionGGX(vec3 N, vec3 H, float roughness)
{
    float a      = roughness*roughness;
    float a2     = a*a;
    float NdotH  = max(dot(N, H), 0.0);
    float NdotH2 = NdotH*NdotH;
	
    float num   = a2;
    float denom = (NdotH2 * (a2 - 1.0) + 1.0);
    denom = PI * denom * denom;
	
    return num / denom;
}

float GeometrySchlickGGX(float NdotV, float roughness)
{
    float r = (roughness + 1.0);
    float k = (r*r) / 8.0;

    float num   = NdotV;
    float denom = NdotV * (1.0 - k) + k;
	
    return num / denom;
}

float GeometrySmith(vec3 N, vec3 V, vec3 L, float roughness)
{
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float ggx2  = GeometrySchlickGGX(NdotV, roughness);
    float ggx1  = GeometrySchlickGGX(NdotL, roughness);
	
    return ggx1 * ggx2;
}

vec3 fresnelSchlick(float cosTheta, vec3 F0)
{
    return F0 + (1.0 - F0) * pow(clamp(1.0 - cosTheta, 0.0, 1.0), 5.0);
}  

void main()
{
    vec2 ScreenAlignedUVs = (ScreenSpaceTransform.xy / ScreenSpaceTransform.z) * 0.5f + 0.5f;

	vec3 Albedo = texture(Buffer_Color, ScreenAlignedUVs).xyz;
    vec3 Normal = texture(Buffer_Normal, ScreenAlignedUVs).xyz;
    vec3 WorldPosition = texture(Buffer_Position, ScreenAlignedUVs).xyz;
    vec4 S_R_M_AO = texture(Buffer_Specular_Roughness_Metalic_AO, ScreenAlignedUVs);

    float Specular   = S_R_M_AO.x;
    float Roughness  = S_R_M_AO.y;
    float Metallic    = S_R_M_AO.z;
    float AO         = S_R_M_AO.w;

    vec3 LightToPixelPos = LightLocation - WorldPosition;
    vec3 V = normalize(CameraLocation - WorldPosition);
    vec3 L = normalize(LightToPixelPos);
    vec3 H = normalize(V + L);

    vec3 F0 = vec3(0.04); 
    F0 = mix(F0, Albedo, Metallic);

    float distance = length(LightToPixelPos);

// ---------------------- calculate light attenuation ---------
// from "DeferredRenderingCommon.ush" line 582

    float Distance2 = distance * distance;
    float DistanceAttenuation = 1 / (Distance2 + 1);


    float LightRadiusMask = Distance2 * InvRadius * InvRadius;

    LightRadiusMask *= LightRadiusMask;
    LightRadiusMask = 1 - LightRadiusMask;
    LightRadiusMask = clamp(LightRadiusMask, 0, 1);

    LightRadiusMask *= LightRadiusMask;

    float Attenuation = DistanceAttenuation * LightRadiusMask;
// ------------------------------------------------------------
    
    vec3 radiance = LightColor * Attenuation;

    float NDF = DistributionGGX(Normal, H, Roughness);
    float G   = GeometrySmith(Normal, V, L, Roughness);      
    vec3 F    = fresnelSchlick(max(dot(H, V), 0.0), F0); 

    vec3 kS = F;
    vec3 kD = vec3(1.0) - kS;
    kD *= 1.0 - Metallic;

    vec3 numerator    = NDF * G * F;
    float denominator = 4.0 * max(dot(Normal, V), 0.0) * max(dot(Normal, L), 0.0) + 0.0001;
    vec3 specular     = numerator / denominator;


    float NdotL = max(dot(Normal, L), 0.0);
    vec3 Lo = (kD * Albedo / PI + specular) * radiance * NdotL;

	Lighting = vec4(Lo, 1);
}