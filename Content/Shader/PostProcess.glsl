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
uniform sampler2D Buffer_Depth;

// -------------------- Fog ---------------------
uniform vec3 FogColor;
uniform float FogAmount;
uniform float FogOffset;
uniform float FogLength;


void main()
{
    vec4 SceneDepth = texture(Buffer_Depth, TexCoords);
    vec4 SceneColor = texture(Buffer_Color, TexCoords);
    
    float FogAlpha = clamp((SceneDepth.x - FogOffset) / FogLength , 0, 1);

    FragColor = mix(SceneColor, vec4(FogColor, 1.0f), FogAlpha * FogAmount);
}