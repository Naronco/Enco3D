#version 120

attribute vec3 in_position;
attribute vec3 in_texCoord;
attribute vec3 in_normal;

varying vec3 worldPos;
varying vec3 texCoord;
varying vec3 normal;

uniform mat4 worldMatrix;
uniform mat4 projectedMatrix;

void main()
{
	worldPos = (worldMatrix * vec4(in_position, 1)).xyz;
	texCoord = in_texCoord;
	normal = mat3(worldMatrix) * in_normal;
	
	gl_Position = projectedMatrix * vec4(in_position, 1);
}