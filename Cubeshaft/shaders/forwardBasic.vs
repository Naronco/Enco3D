#version 120

attribute vec3 in_position;
attribute vec2 in_texCoord;

varying vec2 texCoord;

uniform mat4 worldViewProjectionMatrix;

void main()
{
	texCoord = in_texCoord;
	gl_Position = worldViewProjectionMatrix * vec4(in_position, 1);
}