#version 120

attribute vec3 in_position;
attribute vec2 in_texCoord;
attribute vec3 in_normal;

varying vec2 texCoord;
varying vec3 normal;
varying vec3 worldPos;

uniform mat4 worldMatrix;
uniform mat4 worldViewProjectionMatrix;

void main()
{
	texCoord = in_texCoord;
	normal = mat3(worldMatrix) * in_normal;
	worldPos = vec3(worldMatrix * vec4(in_position, 1.0f));
	
	gl_Position = worldViewProjectionMatrix * vec4(in_position, 1.0f);
}