#version 430 core

layout(location = 0) in vec3 position;
layout(location = 2) in vec2 texCoord;

out vec2 f_TexCoord;

void main(void)
{

	gl_Position = vec4(position, 1);
	f_TexCoord = texCoord;	

}