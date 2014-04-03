#version 330

out vec4 fragColor;

in vec3 texCoord;

uniform sampler2D gbuffer_position;
//uniform sampler2D gbuffer_texCoord;
//uniform sampler2D gbuffer_normal;

void main()
{
	fragColor = vec4(1, 0, 1, 1);//vec4(texture2D(gbuffer_position, texCoord).rgb, 1);
}