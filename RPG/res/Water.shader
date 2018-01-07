#shader vertex
#version 430 core

struct ClipPlane
{
    vec3 Normal;
    float Distance;
};

layout(location = 0) in vec4 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 texCoord;
layout(location = 3) in vec4 color;
layout(location = 4) in vec3 tangent;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

uniform ClipPlane ClippingPlane;

out vec2 f_TexCoord;
out vec3 f_WorldPosition;
out vec3 f_WorldNormal;
out vec3 f_CameraPosition;
out vec4 f_Color;
out vec4 f_ClipPosition;

const float scaling = 50;

void main(void)
{
	vec4 worldPosition = modelMatrix * position;
	vec4 viewPosition = viewMatrix * worldPosition;
	vec4 screenPosition = projectionMatrix * viewPosition;

	gl_ClipDistance[0] = dot(worldPosition, vec4(ClippingPlane.Normal, ClippingPlane.Distance));

	gl_Position = screenPosition;

	f_TexCoord = texCoord * scaling;
	f_WorldPosition = worldPosition.xyz;
	f_WorldNormal = (modelMatrix * vec4(normal, 0)).xyz;
	f_CameraPosition = (inverse(viewMatrix)[3]).xyz;
	f_Color = color;
	f_ClipPosition = screenPosition;
}

#shader fragment
#version 430 core
#include "Lighting.glh"

const int MAX_LIGHTS = 5;

in vec2 f_TexCoord;
in vec3 f_WorldPosition;
in vec3 f_WorldNormal;
in vec3 f_CameraPosition;
in vec4 f_Color;
in vec4 f_ClipPosition;

uniform sampler2D DUDV;
uniform sampler2D Normal;
uniform sampler2D Reflection;
uniform sampler2D Refraction;

uniform vec4 color;
uniform Light Lights[MAX_LIGHTS];
uniform int UsedLights;

uniform float moveFactor;

uniform Material material;

layout(location = 0) out vec4 finalColor;
const float waveStrength = 0.02;

void main(void)
{
	vec4 lightColor = vec4(0.0);
	vec3 toCameraVector = f_CameraPosition - f_WorldPosition;
	vec3 unitToCameraVector = normalize(toCameraVector);

	vec2 ndc = f_ClipPosition.xy / f_ClipPosition.w;
    	vec2 texCoords = ndc / 2.0 + 0.5;
    	vec2 reflectCoords = vec2(texCoords.x, 1.0 - texCoords.y);
    	vec2 refractCoords = vec2(texCoords.x, texCoords.y);

    	vec2 distortedTexCoords = texture(DUDV, vec2(f_TexCoord.x + moveFactor, f_TexCoord.y)).rg * 0.1;
    	distortedTexCoords = f_TexCoord + vec2(distortedTexCoords.x, distortedTexCoords.y + moveFactor);
    	vec2 totalDistortion = (texture(DUDV, distortedTexCoords).rg * 2.0 - 1.0) * waveStrength;

    	vec4 normalMapColor = texture(Normal, distortedTexCoords);
    	vec3 worldNormal = vec3(normalMapColor.r * 2.0 - 1.0, normalMapColor.b * 3.0, normalMapColor.g * 2.0 - 1.0);
    	vec3 unitNormal = normalize(worldNormal);

    	float refractiveFactor = dot(unitToCameraVector, f_WorldNormal);
    	refractiveFactor = pow(refractiveFactor, material.Shininess / 3.0);

    	refractCoords += totalDistortion;
    	refractCoords = clamp(refractCoords, 0.00001, 0.99999);
    	reflectCoords += totalDistortion;
    	reflectCoords = clamp(reflectCoords, 0.00001, 0.99999);

	vec4 refractColor = texture(Refraction, refractCoords);
	vec4 reflectColor = texture(Reflection, reflectCoords);
	vec4 mixColor = mix(reflectColor, refractColor, refractiveFactor);

	for (int i = 0; i < UsedLights; i++)
	{		
		lightColor += CalculateDiffuseColor(Lights[i], material, f_WorldPosition, unitNormal);
		lightColor += CalculateSpecularColor(Lights[i], material, f_WorldPosition, unitNormal, f_CameraPosition);
		lightColor.a = 1.0;
	}
	finalColor = mixColor * color * f_Color * lightColor;
}