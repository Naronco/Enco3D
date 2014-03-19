#version 330

out vec4 fragColor;

in vec2 texCoord;
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
	sampler2D diffuseTexture;
	float specularIntensity, specularExponent;
};

uniform DirectionalLight directionalLight;
uniform Material material;

uniform vec3 eyePos;

void main()
{
	vec3 diffuse = vec3(0, 0, 0);
	vec3 specular = vec3(0, 0, 0);
	
	vec3 diffuseColor = texture(material.diffuseTexture, texCoord).xyz;
	float diffuseIntensity = max(dot(-directionalLight.direction, normal), 0.0);
	diffuseIntensity = clamp(diffuseIntensity, 0.0f, 1.0f);
	diffuseIntensity = int(diffuseIntensity * 3) / 3.0f;
	diffuse = diffuseColor * diffuseIntensity * directionalLight.color;
	
	if(diffuseIntensity > 0.0 && material.specularIntensity > 0.0)
	{
		vec3 reflectionDirection = normalize(reflect(directionalLight.direction, normal));
		vec3 viewDirection = normalize(eyePos - worldPos);
		float specularIntensity = dot(viewDirection, reflectionDirection);
		specularIntensity = pow(specularIntensity, material.specularExponent);
		specularIntensity = clamp(diffuseIntensity, 0.0f, 1.0f);
		specularIntensity = int(diffuseIntensity * 3) / 3.0f;
		
		if(specularIntensity > 0.0)
		{
			specular = material.specularIntensity * specularIntensity * directionalLight.color;
		}
	}
	
	fragColor = vec4(diffuse + specular, 1);
}