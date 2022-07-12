#type vertex
#version 460 core

layout (location = 0) in vec2 aPos;
layout (location = 1) in vec2 aTexCoords;

out vec2 TexCoords;

void main()
{
    gl_Position = vec4(aPos.x, aPos.y, 0.0, 1.0); 
    TexCoords = aTexCoords;
}  


#type fragment
#version 460 core

layout(location = 6) out vec4 Buffer_FinalColor;
  
in vec2 TexCoords;

uniform sampler2D Buffer_Position;
uniform sampler2D Buffer_Color;
uniform sampler2D Buffer_Normal;
uniform sampler2D Buffer_Specular_Roughness_Metalic_AO;
uniform usampler2D Buffer_ShadingModel;
uniform sampler2D Buffer_Lighting;
uniform usampler2D Buffer_Stencil;
uniform sampler2D Buffer_Depth;
uniform sampler2D ShadowMap;


uniform samplerCube EnvironmentCubemap;


uniform mat4 LightMatrix;
uniform mat4 Projection;

uniform vec3 CameraLocation;
uniform vec3 LightDirection;
uniform vec3 LightLocation;

// -------------------- Light -------------------
uniform vec3 AmbientLightColor;
uniform float AmbientLightIntensity;

uniform vec3 DiffuseLightColor;
uniform float DiffuseLightIntensity;
uniform vec3 DiffuseLightDirection;

void main()
{
    vec4 SceneColor = texture(Buffer_Color, TexCoords);
    vec3 Normal = texture(Buffer_Normal, TexCoords).xyz;
    vec3 WorldPosition = texture(Buffer_Position, TexCoords).xyz;
    vec4 S_R_M_AO = texture(Buffer_Specular_Roughness_Metalic_AO, TexCoords);

    float Specular   = S_R_M_AO.x;
    float Roughness  = S_R_M_AO.y;
    float Metallic    = S_R_M_AO.z;
    float AO         = S_R_M_AO.w;
    uint FragShadingModel = texture(Buffer_ShadingModel, TexCoords).r;
    vec3 Lighting = texture(Buffer_Lighting, TexCoords).xyz;

    float SceneDepth = texture(Buffer_Depth, TexCoords).x;
    uint StencilMask = texture(Buffer_Stencil, TexCoords).x;

    // Environment reflection
    vec3 CameraDirection = normalize(WorldPosition - CameraLocation);
    vec3 ReflectionVector = reflect(CameraDirection, Normal);
    ReflectionVector = ReflectionVector.xzy;

    vec4 EnvironmentReflection = texture(EnvironmentCubemap, ReflectionVector);


    vec4 LightSpacePoition = Projection * LightMatrix * vec4(WorldPosition, 1);
    
    float w = LightSpacePoition.w != 0 ? LightSpacePoition.w : 1.0f;
    vec3 C = LightSpacePoition.xyz / w;
    C = C * 0.5f + 0.5f;

    vec2 Uv = C.xy;

    float Shadow;;
    float bias = 0.001;
    float D = texture(ShadowMap, Uv).x;
    Shadow = C.z - bias > D ? 1.0f : 0.0f;

    float CameraFacing = dot(LightDirection, WorldPosition - LightLocation);

    if(Uv.x < 0.01 || Uv.x > 0.99 || Uv.y < 0.01 || Uv.y > 0.99 || CameraFacing < 0)
    {
        Shadow = 0;
    }

    vec3 FinalColor = SceneColor.xyz;

    // Lit
    if(FragShadingModel == 0)
    {
       // Light
       vec3 AmbientLight = AmbientLightColor * AmbientLightIntensity;
       vec3 DiffuseLight = DiffuseLightColor * max(dot(Normal, -DiffuseLightDirection), 0) * DiffuseLightIntensity;

       vec3 ViewDirection = normalize(CameraLocation - WorldPosition);
       vec3 ReflectionVector = reflect(-DiffuseLightDirection, Normal);
    
       float SpecularLightFactor = pow(max(dot(ViewDirection, ReflectionVector), 0), Specular * 32);
   
       DiffuseLight *= (1 + SpecularLightFactor);

       FinalColor = FinalColor * vec3((AmbientLight + DiffuseLight * (1 - Shadow)));

       FinalColor += Lighting;

       // Reflection
       FinalColor = mix(EnvironmentReflection.xyz, FinalColor, Roughness);
    }



    FinalColor = FinalColor/ (FinalColor + 1);
    FinalColor = pow(FinalColor, vec3(2.2f));

    Buffer_FinalColor = vec4(FinalColor, 1);
}