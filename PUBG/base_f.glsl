#version 430 core

in vec2 f_TexCoord;

uniform sampler2D tex0;

layout(location = 0) out vec4 finalColor;

void main(void)
{
	finalColor = texture(tex0, f_TexCoord);
}