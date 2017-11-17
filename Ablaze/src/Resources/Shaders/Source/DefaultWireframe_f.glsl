R"(
#version 430 core

in vec2 f_TexCoord;
in vec4 f_Color;

uniform vec4 color;

layout(location = 0) out vec4 finalColor;

void main(void)
{
	finalColor = f_Color * color;
}
)"