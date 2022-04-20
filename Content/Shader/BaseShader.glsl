#type vertex
#version 460 core
uniform vec3 CameraPosition;
uniform vec3 CameraRotation;
uniform mat4 view;

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 VColor;
out vec4 V_Color;
void main()
{
	gl_Position = view * vec4(aPos, 1.0f);	
	//gl_Position = vec4(aPos, 1.0f);

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