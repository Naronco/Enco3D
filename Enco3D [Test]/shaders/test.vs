#version 120

attribute vec3 in_position;
attribute vec2 in_texCoord;
attribute vec3 in_color;

uniform mat4 worldViewProjectionMatrix;

varying vec2 texCoord;
varying vec3 color;

void main()
{
	texCoord = in_texCoord;
	color = in_color;
	gl_Position = worldViewProjectionMatrix * vec4(in_position, 1);
}