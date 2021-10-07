
#type vertex
#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 VColor;
out vec4 V_Color;
void main()
{
   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
	V_Color = VColor;
}


#type fragment
#version 460 core
out vec4 FragColor;
in vec4 V_Color;
void main()
{
	FragColor = V_Color;
}