#version 120

attribute vec3 in_position;
attribute vec3 in_texCoord;

varying vec3 texCoord;

uniform mat4 matrix_worldViewProjectionMatrix;

void main()
{
	texCoord = in_texCoord;
	gl_Position = matrix_worldViewProjectionMatrix * vec4(in_position, 1.0f);
}