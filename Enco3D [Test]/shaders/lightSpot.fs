#version 330

out vec4 fragColor;

in vec3 texCoord;
in vec3 normal;
in vec3 worldPos;

struct SpotLight
{
	vec3 color;
	float intensity;
	vec3 position, direction;
	float range, cutoff, exponent;
};

struct Material
{
	vec3 diffuseColor;
	sampler2D diffuseTexture;
	float specularIntensity, specularExponent;
};

uniform SpotLight spotLight;
uniform Material material;

uniform vec3 eyePos;

void main()
{
	vec3 diffuse = vec3(0, 0, 0);
	vec3 specular = vec3(0, 0, 0);
	
	vec3 lightDirection = worldPos - spotLight.position;
	float distanceToLight = length(lightDirection);
	
	if(distanceToLight < spotLight.range)
	{
		lightDirection = normalize(lightDirection);
		float spotLightFactor = dot(lightDirection, spotLight.direction);
		
		if(spotLightFactor > spotLight.cutoff)
		{
			spotLightFactor = 1.0f - (1.0f - spotLightFactor) / (1.0f - spotLight.cutoff);
			float attenuation = 1.0f - (distanceToLight / spotLight.range);
			
			vec3 diffuseColor = texture(material.diffuseTexture, texCoord.xy).xyz * material.diffuseColor;
			float diffuseIntensity = max(dot(-lightDirection, normal), 0.0) * attenuation * spotLightFactor;
			diffuse = diffuseColor * diffuseIntensity * spotLight.color;
			
			if(diffuseIntensity > 0.0 && material.specularIntensity > 0.0)
			{
				vec3 reflectionDirection = normalize(reflect(lightDirection, normal));
				vec3 viewDirection = normalize(eyePos - worldPos);
				float specularIntensity = dot(viewDirection, reflectionDirection);
				specularIntensity = pow(specularIntensity, material.specularExponent);
				
				if(specularIntensity > 0.0)
				{
					specular = material.specularIntensity * specularIntensity * spotLight.color * attenuation * spotLightFactor;
				}
			}
		}
	}
	
	fragColor = vec4(diffuse + specular, 1);
}