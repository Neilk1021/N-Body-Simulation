#shader vertex
#version 330 core 

layout(location = 0) in vec4 position; 
layout(location = 1) in vec3 aColor; 
out vec3 ourColor; 
 
uniform mat4 u_MVP;
uniform vec4 u_Cam;

void main() 
{ 
	gl_Position = u_MVP * (position + u_Cam);
	ourColor = aColor;  
} ;


#shader fragment
#version 330 core 
 
layout(location = 0) out vec4 color; 
in vec3 ourColor; 
uniform vec4 u_Color;
uniform vec2 u_resolution;


void main() 
{
	color = u_Color;
	//color = vec4(ourColor, 1.0f)* u_Color;
} ;