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

layout(location = 7) out vec4 Buffer_Postproccess;
  
in vec2 TexCoords;

uniform sampler2D Buffer_Position;
uniform sampler2D Buffer_Color;
uniform sampler2D Buffer_Normal;
uniform sampler2D Buffer_Specular_Roughness_Metalic_AO;
uniform usampler2D Buffer_ShadingModel;
uniform sampler2D Buffer_Lighting;
uniform usampler2D Buffer_Stencil;
uniform sampler2D Buffer_Depth;
uniform sampler2D Buffer_FinalColor;
uniform sampler2D ShadowMap;

uniform int DisplayBufer;

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
    vec4 FinalColor = texture(Buffer_FinalColor, TexCoords);

    float Specular   = S_R_M_AO.x;
    float Roughness  = S_R_M_AO.y;
    float Metallic    = S_R_M_AO.z;
    float AO         = S_R_M_AO.w;
    uint FragShadingModel = texture(Buffer_ShadingModel, TexCoords).r;
    vec3 Lighting = texture(Buffer_Lighting, TexCoords).xyz;

    float SceneDepth = texture(Buffer_Depth, TexCoords).x;
    uint StencilMask = texture(Buffer_Stencil, TexCoords).x;

    vec4 PostproccessColor = FinalColor;    

    // blur
    for(int k = 1; k <= BlurStepNumber; k++)
    {
        for(int i = -1; i <= 1; i++)
        {
            for(int j = -1; j <= 1; j++)
            {
                PostproccessColor += texture(Buffer_FinalColor, TexCoords + (vec2(i, j) * BlurStepSize) * k);
            }
        }
    }
    PostproccessColor /= BlurStepNumber * 8 + 1;


    // fog
    float FogAlpha = clamp((SceneDepth - FogOffset) / FogLength , 0, 1);
    PostproccessColor = mix(PostproccessColor, vec4(FogColor, 1.0f), FogAlpha * FogAmount);
    

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
            PostproccessColor = vec4(1.0f, 0.75f, 0.4f, 1.0f);
    }

    switch(DisplayBufer)
    {
        // final color
        case 0:
           Buffer_Postproccess = PostproccessColor; 
        break;
        
        // scene color
        case 1:
           Buffer_Postproccess = FinalColor; 
        break;

        // base color
        case 2:
           Buffer_Postproccess = SceneColor; 
        break;

        // world normal
        case 3:
           Buffer_Postproccess = vec4(Normal, 1); 
        break;

        // scene depth
        case 4:
           Buffer_Postproccess = vec4(SceneDepth);
        break;

        // stencil
        case 5:
           Buffer_Postproccess = vec4(StencilMask / 255.0f);
        break;
        
        // specular
        case 6:
           Buffer_Postproccess = vec4(Specular);
        break;

        // roughness
        case 7:
           Buffer_Postproccess = vec4(Roughness);
        break;

        // metallic
        case 8:
           Buffer_Postproccess = vec4(Metallic);
        break;

        // ao
        case 9:
           Buffer_Postproccess = vec4(AO);
        break;
        
        // shading model
        case 10:
           if(FragShadingModel == 0)
           {
               Buffer_Postproccess = vec4(1.0f, 0.0f, 0.0f, 1.0f);
           }
           else if(FragShadingModel == 1)
           {
               Buffer_Postproccess = vec4(0.0f, 1.0f, 0.0f, 1.0f);
           }
           else
           {
               Buffer_Postproccess = vec4(0.0f, 0.0f, 1.0f, 1.0f);
           }
        break;

        case 11:
            Buffer_Postproccess = vec4(Lighting, 1);
        break;

        default:
           Buffer_Postproccess = PostproccessColor; 
        break;
    }
}