/*#version 120

varying vec2 texCoord;

uniform vec3 color;
uniform sampler2D diffuseTexture;

void main()
{
	gl_FragColor = texture2D(diffuseTexture, texCoord.xy) * vec4(color, 1);
}*/

#version 330

out vec4 fragColor;

in vec2 texCoord;

uniform vec3 color;
uniform sampler2D diffuseTexture;

void main()
{
	fragColor = texture(diffuseTexture, texCoord.xy) * vec4(color, 1);
}