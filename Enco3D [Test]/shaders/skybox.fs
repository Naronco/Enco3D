#version 330

out vec4 fragColor;

in vec3 worldPos;

uniform samplerCube skyboxTexture;

void main()
{
	fragColor = texture(skyboxTexture, normalize(worldPos));
}