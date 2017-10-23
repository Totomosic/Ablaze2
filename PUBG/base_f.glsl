#version 330 core

in vec2 f_TexCoord;

uniform sampler2D Tex0;

layout(location = 0) out vec4 finalColor;

void main(void)
{
	finalColor = texture(Tex0, f_TexCoord);
}