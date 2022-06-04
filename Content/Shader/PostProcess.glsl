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

layout(location = 0) out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D Buffer_Position;
uniform sampler2D Buffer_Color;
uniform sampler2D Buffer_Normal;
uniform sampler2D Buffer_Specular_Roughness_Metalic_AO;
uniform usampler2D Buffer_Stencil;
uniform sampler2D Buffer_Depth;
uniform sampler2D ShadowMap;

uniform mat4 LightMatrix;
uniform mat4 View;
uniform mat4 Projection;

uniform vec3 CameraLocation;
uniform vec3 LightDirection;
uniform vec3 LightLocation;

uniform int DisplayBufer;

// -------------------- Light -------------------
uniform vec3 AmbientLightColor;
uniform float AmbientLightIntensity;

uniform vec3 DiffuseLightColor;
uniform float DiffuseLightIntensity;
uniform vec3 DiffuseLightDirection;

// -------------------- Fog ---------------------
uniform vec3 FogColor;
uniform float FogAmount;
uniform float FogOffset;
uniform float FogLength;

// -------------------- Blur --------------------
uniform float BlurStepSize;
uniform int BlurStepNumber;

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

    float SceneDepth = texture(Buffer_Depth, TexCoords).x;
    uint StencilMask = texture(Buffer_Stencil, TexCoords).x;

    vec4 LightSpacePoition = Projection * LightMatrix * vec4(WorldPosition, 1);
    
    float w = LightSpacePoition.w != 0 ? LightSpacePoition.w : 1.0f;
    vec3 C = LightSpacePoition.xyz / w;
    //vec3 C = LightSpacePoition.xyz;
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
        //Uv = vec2(0);
    }


    vec4 Color = SceneColor;
    

    // light

    if(StencilMask != 64)
    {
       vec3 AmbientLight = AmbientLightColor * AmbientLightIntensity;
       vec3 DiffuseLight = DiffuseLightColor * max(dot(Normal, -DiffuseLightDirection), 0) * DiffuseLightIntensity;

       vec3 ViewDirection = normalize(CameraLocation - WorldPosition);
       vec3 ReflectionVector = reflect(-DiffuseLightDirection, Normal);
    
       float SpecularLightFactor = pow(max(dot(ViewDirection, ReflectionVector), 0), Specular * 32);
   
       DiffuseLight *= (1 + SpecularLightFactor);

       Color = Color * vec4((AmbientLight + DiffuseLight * (1 - Shadow)), 1);
    }


    // blur
    for(int k = 1; k <= BlurStepNumber; k++)
    {
        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                Color += texture(Buffer_Color, TexCoords + (vec2(i, j) * BlurStepSize) * k);
            }
        }
    }
    Color /= BlurStepNumber * 8 + 1;


    // fog
    float FogAlpha = clamp((SceneDepth - FogOffset) / FogLength , 0, 1);
    Color = mix(Color, vec4(FogColor, 1.0f), FogAlpha * FogAmount);
    

    // is selected in editor
    if(StencilMask >= 128)
    {
        float StepSize = 0.01f;
        StepSize *= SceneDepth * 0.2f;

        uint SelectedNeighborFragmentNumber = 0;

        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                if(texture(Buffer_Stencil, TexCoords + (vec2(i, j) * StepSize)).x >= 128)
                    SelectedNeighborFragmentNumber++;
            }
        }

        if(SelectedNeighborFragmentNumber < 7)
            Color = vec4(1.0f, 0.75f, 0.4f, 1.0f);
    }

    switch(DisplayBufer)
    {
        // final color
        case 0:
           FragColor = Color; 
           //FragColor = vec4(Shadow); 
           //FragColor = vec4(Uv, 0, 1.0);
           //FragColor = vec4(C.z);
           //FragColor = vec4(LightSpacePoition.w);
           //FragColor = vec4(D);
           //FragColor = vec4(CameraFacing);
        break;

        // base color
        case 1:
           FragColor = SceneColor; 
        break;

        // world normal
        case 2:
           FragColor = vec4(Normal, 1); 
        break;

        // scene depth
        case 3:
           FragColor = vec4(SceneDepth);
        break;

        // stencil
        case 4:
           FragColor = vec4(StencilMask / 255.0f);
        break;
        
        // specular
        case 5:
           FragColor = vec4(Specular);
        break;

        // roughness
        case 6:
           FragColor = vec4(Roughness);
        break;

        // metallic
        case 7:
           FragColor = vec4(Metallic);
        break;

        // ao
        case 8:
           FragColor = vec4(AO);
        break;



        default:
           FragColor = Color; 
        break;
    }
}