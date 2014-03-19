#version 330

out vec4 fragColor;

in vec2 texCoord;
in vec3 normal;
in vec3 worldPos;

struct PointLight
{
	vec3 color;
	float intensity;
	vec3 position;
	float range;
};

struct Material
{
	sampler2D diffuseTexture;
	float specularIntensity, specularExponent;
};

uniform PointLight pointLight;
uniform Material material;

uniform vec3 eyePos;

void main()
{
	vec3 diffuse = vec3(0, 0, 0);
	vec3 specular = vec3(0, 0, 0);
	
	vec3 lightDirection = worldPos - pointLight.position;
	float distanceToLight = length(lightDirection);
	
	if(distanceToLight < pointLight.range)
	{
		lightDirection = normalize(lightDirection);
		float attenuation = 1.0f - (distanceToLight / pointLight.range);
		
		vec3 diffuseColor = texture(material.diffuseTexture, texCoord).xyz;
		float diffuseIntensity = max(dot(-lightDirection, normal), 0.0) * attenuation;
		diffuseIntensity = clamp(diffuseIntensity, 0.0f, 1.0f);
		diffuseIntensity = int(diffuseIntensity * 3) / 3.0f;
		diffuse = diffuseColor * diffuseIntensity * pointLight.color;
		
		if(diffuseIntensity > 0.0 && material.specularIntensity > 0.0)
		{
			vec3 reflectionDirection = normalize(reflect(lightDirection, normal));
			vec3 viewDirection = normalize(eyePos - worldPos);
			float specularIntensity = dot(viewDirection, reflectionDirection);
			specularIntensity = pow(specularIntensity, material.specularExponent);
			specularIntensity = clamp(diffuseIntensity, 0.0f, 1.0f);
			specularIntensity = int(diffuseIntensity * 3) / 3.0f;
			
			if(specularIntensity > 0.0)
			{
				specular = material.specularIntensity * specularIntensity * pointLight.color * attenuation;
			}
		}
	}
	
	fragColor = vec4(diffuse + specular, 1);
}