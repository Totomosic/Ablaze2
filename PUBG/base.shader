#shader vertex
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 2) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 f_TexCoord;

void main(void)
{
	vec4 worldPosition = modelMatrix * position;
	vec4 viewPosition = viewMatrix * worldPosition;
	vec4 screenPosition = projectionMatrix * viewPosition;
	gl_Position = screenPosition;
	
	f_TexCoord = texCoord;
}

#shader fragment
#version 430 core

in vec2 f_TexCoord;

uniform sampler2D Tex0;

layout(location = 0) out vec4 finalColor;

void main(void)
{
	finalColor = texture(Tex0, f_TexCoord);
}