#version 120

// Attributes
attribute vec3 in_position;
attribute vec3 in_texCoord;
attribute vec3 in_normal;

// Varyings
varying vec3 texCoord;
varying vec3 normal;
varying vec3 worldViewPos;
varying vec4 worldViewProjectionPos;
varying vec4 prevWorldViewProjectionPos;

// Uniforms
uniform mat4 matrix_worldMatrix;
uniform mat4 matrix_worldViewMatrix;
uniform mat4 matrix_worldViewProjectionMatrix;
uniform mat4 matrix_prevWorldViewProjectionMatrix;

void main()
{
	texCoord = in_texCoord;
	normal = normalize(mat3(matrix_worldViewMatrix) * in_normal);
	worldViewPos = vec3(matrix_worldViewMatrix * vec4(in_position, 1.0f));
	worldViewProjectionPos = matrix_worldViewProjectionMatrix * vec4(in_position, 1.0f);
	prevWorldViewProjectionPos = matrix_prevWorldViewProjectionMatrix * vec4(in_position, 1.0f);
	gl_Position = worldViewProjectionPos;
}