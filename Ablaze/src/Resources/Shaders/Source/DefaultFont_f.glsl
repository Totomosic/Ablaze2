R"(#version 430 core

in vec2 f_TexCoord;
in vec3 f_WorldPosition;
in vec3 f_WorldNormal;
in vec3 f_CameraPosition;
in vec4 f_Color;

uniform vec4 color;
uniform sampler2D Tex0;

layout(location = 0) out vec4 finalColor;

void main(void)
{
	finalColor = color * f_Color;
	finalColor.a = texture(Tex0, f_TexCoord).r * color.a * f_Color.a;
})"