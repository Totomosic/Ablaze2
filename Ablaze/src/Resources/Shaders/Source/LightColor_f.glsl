R"(#version 430 core

struct Light
{
	vec3 Position;
	vec4 Color;
	float Ambient;
};

const int MAX_LIGHTS = 5;

in vec2 f_TexCoord;
in vec3 f_WorldPosition;
in vec3 f_WorldNormal;
in vec4 f_Color;

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
		lightColor.a = 1.0;
	}
	finalColor = color * f_Color * lightColor;
})"