R"(#version 430 core

struct Material
{
	float Shininess;
	float ShineDamper;
	vec4 SpecularHighlight;
};

struct Light
{
	vec3 Position;
	vec4 Color;
	float Ambient;
};

vec4 CalculateDiffuseColor(Light light, Material material, vec3 worldPosition, vec3 worldNormal)
{
	vec3 toLightVector = light.Position - worldPosition;
	vec3 unitToLightVector = normalize(toLightVector);
	vec3 unitNormal = normalize(worldNormal);
	float nDotV = dot(unitNormal, unitToLightVector);
	vec4 color = light.Color * max(nDotV, light.Ambient);
	color.a = light.Color.a;
	return color;
}

vec4 CalculateSpecularColor(Light light, Material material, vec3 worldPosition, vec3 worldNormal, vec3 cameraPosition)
{
	vec3 toLightVector = light.Position - worldPosition;
	vec3 unitToLightVector = normalize(toLightVector);
	vec3 unitNormal = normalize(worldNormal);
	vec3 toCameraVector = cameraPosition - worldPosition;
	vec3 unitToCameraVector = normalize(toCameraVector);
	vec3 lightDirection = -unitToLightVector;
	vec3 reflectedLightDirection = reflect(lightDirection, unitNormal);
	float specularFactor = max(dot(reflectedLightDirection, unitToCameraVector), 0.0);
    float dampedSpecularFactor = pow(specularFactor, material.ShineDamper); 
	return light.Color * dampedSpecularFactor * material.Shininess * material.SpecularHighlight;
}

const int MAX_LIGHTS = 5;

in vec2 f_TexCoord;
in vec3 f_WorldPosition;
in vec3 f_WorldNormal;
in vec3 f_CameraPosition;
in vec4 f_Color;

uniform vec4 color;
uniform Light Lights[MAX_LIGHTS];
uniform int UsedLights;

uniform Material material;

layout(location = 0) out vec4 finalColor;

void main(void)
{
	vec4 lightColor = vec4(0.0);
	for (int i = 0; i < UsedLights; i++)
	{
		lightColor += CalculateDiffuseColor(Lights[i], material, f_WorldPosition, f_WorldNormal);
		lightColor += CalculateSpecularColor(Lights[i], material, f_WorldPosition, f_WorldNormal, f_CameraPosition);
		lightColor.a = 1.0;
	}
	finalColor = color * f_Color * lightColor;
})"