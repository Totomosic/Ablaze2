#version 430 core

layout(location = 0) in vec2 position;
layout(location = 1) in vec2 texCoord;

out vec2 f_TexCoord;

void main(void)
{

	gl_Position = vec4(position, 0, 1);
	f_TexCoord = texCoord;	

}