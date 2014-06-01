#version 120

attribute vec3 in_position;
attribute vec3 in_texCoord;
attribute vec3 in_normal;

varying vec3 texCoord;
varying vec3 normal;
varying vec3 worldPos;

uniform mat4 matrix_worldMatrix;
uniform mat4 matrix_worldViewProjectionMatrix;

void main()
{
	texCoord = in_texCoord;
	normal = mat3(matrix_worldMatrix) * in_normal;
	worldPos = vec3(matrix_worldMatrix * vec4(in_position, 1.0f));
	
	gl_Position = matrix_worldViewProjectionMatrix * vec4(in_position, 1.0f);
}