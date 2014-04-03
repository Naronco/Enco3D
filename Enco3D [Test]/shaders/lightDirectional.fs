#version 330

out vec4 fragColor;

in vec3 texCoord;
in vec3 normal;
in vec3 worldPos;

struct DirectionalLight
{
	vec3 color;
	float intensity;
	vec3 direction;
};

struct Material
{
	vec3 diffuseColor;
	sampler2D diffuseTexture;
	float specularIntensity, specularExponent;
	float reflectionIntensity;
};

uniform DirectionalLight directionalLight;
uniform Material material;

uniform samplerCube environmentTexture;

uniform vec3 eyePos;

void main()
{
	vec3 diffuse = vec3(0, 0, 0);
	vec3 specular = vec3(0, 0, 0);
	
	vec3 diffuseColor = texture(material.diffuseTexture, texCoord.xy).xyz * material.diffuseColor;
	float diffuseIntensity = max(dot(-directionalLight.direction, normal), 0.0);
	diffuse = diffuseColor * diffuseIntensity * directionalLight.color;
	
	if(diffuseIntensity > 0.0 && material.specularIntensity > 0.0)
	{
		vec3 reflectionDirection = normalize(reflect(directionalLight.direction, normal));
		vec3 viewDirection = normalize(eyePos - worldPos);
		float specularIntensity = dot(viewDirection, reflectionDirection);
		specularIntensity = pow(specularIntensity, material.specularExponent);
		
		if(specularIntensity > 0.0)
		{
			specular = material.specularIntensity * specularIntensity * directionalLight.color;
		}
	}
	
	fragColor = vec4(diffuse + specular, 1);
	
	if(material.reflectionIntensity > 0.0f)
	{
		vec3 viewDirection = normalize(worldPos - eyePos);
		vec3 reflectionDirection = normalize(reflect(viewDirection, normal));
		vec4 reflectedEnvironmentColor = texture(environmentTexture, reflectionDirection);
		
		fragColor = (1.0f - material.reflectionIntensity) * fragColor + material.reflectionIntensity * reflectedEnvironmentColor;
	}
}