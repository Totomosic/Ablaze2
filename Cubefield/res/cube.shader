#shader vertex
#version 430 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform float time;

out vec2 g_TexCoord;
out vec4 g_Color;
out vec3 g_Normal;

void main(void)
{
    vec4 worldPosition = modelMatrix * vec4(position, 1.0);
    vec4 viewPosition = viewMatrix * worldPosition;
    vec4 screenPosition = projectionMatrix * viewPosition;
    gl_Position = screenPosition;

    g_TexCoord = texCoord;
    g_Color = color;
    g_Normal = normalize((modelMatrix * vec4(normal, 0.0)).xyz);
}

#shader geometry
#version 430 core

layout(triangles) in;
layout(triangle_strip, max_vertices=6) out;

in vec2 g_TexCoord[];
in vec4 g_Color[];
in vec3 g_Normal[];

out vec4 f_Color;

void main(void)
{
    gl_Position = gl_in[0].gl_Position;
    f_Color = g_Color[0];
    EmitVertex();
    gl_Position = gl_in[1].gl_Position;
    f_Color = g_Color[1];
    EmitVertex();
    gl_Position = gl_in[2].gl_Position;
    f_Color = g_Color[2];
    EmitVertex();
    EndPrimitive();

    gl_Position = gl_in[0].gl_Position + vec4(g_Normal[0], 0.0);
    f_Color.xyz = 1 - g_Color[0].xyz;
    EmitVertex();
    gl_Position = gl_in[1].gl_Position + vec4(g_Normal[1], 0.0);
    f_Color.xyz = 1 - g_Color[1].xyz;
    EmitVertex();
    gl_Position = gl_in[2].gl_Position + vec4(g_Normal[2], 0.0);
    f_Color.xyz = 1 - g_Color[2].xyz;
    EmitVertex();
    EndPrimitive();
}

#shader fragment
#version 430 core

in vec4 f_Color;

uniform vec4 color;

layout(location = 0) out vec4 finalColor;

void main(void)
{
    finalColor = f_Color * color;    
}