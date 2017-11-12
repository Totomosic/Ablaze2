#shader vertex
#version 430 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 f_TexCoord;
out vec3 f_WorldNormal;
out vec3 f_WorldPosition;
out vec3 f_CameraPosition;

void main(void)
{
	vec4 worldPosition = modelMatrix * position;
	vec4 viewPosition = viewMatrix * worldPosition;
	vec4 screenPosition = projectionMatrix * viewPosition;
	gl_Position = screenPosition;
	
	f_TexCoord = texCoord;
	f_WorldNormal = (modelMatrix * vec4(normal, 0)).xyz;
	f_WorldPosition = worldPosition.xyz;
	f_CameraPosition = inverse(viewMatrix)[3].xyz;
}

#shader fragment
#version 430 core

struct Light
{
	vec3 Position;
	vec4 Color;
	float Ambient;
};

const int MAX_LIGHTS = 5;

in vec2 f_TexCoord;
in vec3 f_WorldNormal;
in vec3 f_WorldPosition;
in vec3 f_CameraPosition;

uniform sampler2D Tex0;
uniform vec4 color;
uniform Light Lights[MAX_LIGHTS];
uniform int UsedLights;

layout(location = 0) out vec4 finalColor;

void main(void)
{
	vec4 lightColor = vec4(1.0);
	for (int i = 0; i < UsedLights; i++)
	{
		vec3 toLightVector = Lights[i].Position - f_WorldPosition;
		vec3 unitToLightVector = normalize(toLightVector);
		vec3 unitNormal = normalize(f_WorldNormal);
		float nDotV = dot(unitNormal, unitToLightVector);
		lightColor *= Lights[i].Color * max(nDotV, Lights[i].Ambient);
	}
	lightColor.a = 1;
	finalColor = texture(Tex0, f_TexCoord) * color * lightColor;
}









