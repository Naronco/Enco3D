#version 330

out vec4 fragColor;

in vec2 texCoord;

uniform vec3 globalAmbientLight;

uniform vec3 diffuseColor;
uniform sampler2D diffuseTexture;

void main()
{
	fragColor = texture(diffuseTexture, texCoord.xy) * vec4(diffuseColor, 1.0f) * vec4(globalAmbientLight, 1);
}