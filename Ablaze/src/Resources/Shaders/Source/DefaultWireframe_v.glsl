R"(
#version 430 core

struct ClipPlane
{
    vec3 Normal;
    float Distance;
};

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform ClipPlane ClippingPlane;

out vec2 g_TexCoord;
out vec4 g_Color;

void main(void)
{
	vec4 worldPosition = modelMatrix * vec4(position, 1.0);
	vec4 viewPosition = viewMatrix * worldPosition;
	vec4 screenPosition = projectionMatrix * viewPosition;

	gl_ClipDistance[0] = dot(worldPosition, vec4(ClippingPlane.Normal, ClippingPlane.Distance));

	gl_Position = screenPosition;

	g_TexCoord = texCoord;
	g_Color = color;
}
)"