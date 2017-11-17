R"(
#version 430 core

layout(triangles) in;
layout(line_strip, max_vertices = 6) out;

in vec2 g_TexCoord[];
in vec4 g_Color[];

out vec2 f_TexCoord;
out vec4 f_Color;

void main(void)
{
	gl_Position = gl_in[0].gl_Position;
	f_TexCoord = g_TexCoord[0];
	f_Color = g_Color[0];
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	f_TexCoord = g_TexCoord[1];
	f_Color = g_Color[1];
	EmitVertex();
	EndPrimitive();

	gl_Position = gl_in[0].gl_Position;
	f_TexCoord = g_TexCoord[0];
	f_Color = g_Color[0];
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	f_TexCoord = g_TexCoord[2];
	f_Color = g_Color[2];
	EmitVertex();
	EndPrimitive();

	gl_Position = gl_in[1].gl_Position;
	f_TexCoord = g_TexCoord[1];
	f_Color = g_Color[1];
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	f_TexCoord = g_TexCoord[2];
	f_Color = g_Color[2];
	EmitVertex();
	EndPrimitive();
}
)"