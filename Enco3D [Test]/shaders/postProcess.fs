#version 330

out vec4 fragColor;

in vec2 texCoord;

uniform sampler2D gbuffer_position;
uniform sampler2D gbuffer_texCoord;
uniform sampler2D gbuffer_normal;
uniform sampler2D gbuffer_depth;

void main()
{
	fragColor = vec4(texture2D(gbuffer_position, texCoord).rgb, 1);
}