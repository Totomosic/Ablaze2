#shader vertex
#version 430 core

layout(location = 0) in vec4 position;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 f_WorldPosition;

void main(void)
{
	vec4 worldPosition = modelMatrix * position;
	vec4 viewPosition = viewMatrix * worldPosition;
	vec4 screenPosition = projectionMatrix * viewPosition;
	gl_Position = screenPosition;

	f_WorldPosition = worldPosition.xy;
}

#shader fragment
#version 430 core

struct Metaball
{
	vec2 Position;
	float Radius;
	vec4 Color;
};

in vec2 f_WorldPosition;

uniform vec4 color;
uniform Metaball Metaballs[20];
uniform int ballCount;

layout(location = 0) out vec4 finalColor;

void main(void)
{	
	vec3 sum = vec3(0);
	for (int i = 0; i < ballCount; i++)
	{
		float dist = length(Metaballs[i].Position - f_WorldPosition);
		float color = Metaballs[i].Radius / dist;
		sum += color * Metaballs[i].Color.xyz;
	}

	finalColor = vec4(sum, 1.0) * color;
}