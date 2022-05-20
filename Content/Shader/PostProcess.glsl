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

out vec4 FragColor;
  
in vec2 TexCoords;

uniform sampler2D Buffer_Color;
uniform sampler2D Buffer_Normal;
uniform usampler2D Buffer_Stencil;
uniform sampler2D Buffer_Depth;


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

    float SceneDepth = texture(Buffer_Depth, TexCoords).x;
    uint StencilMask = texture(Buffer_Stencil, TexCoords).x;

    vec4 Color = SceneColor;
    
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

    FragColor = vec4(Normal, 1);
    //FragColor = Color;
    //FragColor = vec4(StencilMask / 255.0);
    //FragColor = vec4(SceneDepth);
    //FragColor = vec4(SceneDepth * StencilMask / 255.0f) * Color;
}