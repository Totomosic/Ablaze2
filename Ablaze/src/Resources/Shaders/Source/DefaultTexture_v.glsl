R"(#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;
layout(location = 4) in vec3 tangent;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 f_TexCoord;
out vec3 f_WorldPosition;
out vec3 f_WorldNormal;
out vec4 f_Color;

void main(void)
{
	vec4 worldPosition = modelMatrix * position;
	vec4 viewPosition = viewMatrix * worldPosition;
	vec4 screenPosition = projectionMatrix * viewPosition;
	gl_Position = screenPosition;

	f_TexCoord = texCoord;
	f_WorldPosition = worldPosition.xyz;
	f_WorldNormal = (modelMatrix * vec4(normal, 0)).xyz;
	f_Color = color;
})"