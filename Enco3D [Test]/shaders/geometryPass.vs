/*#version 330

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec2 in_texCoord;
layout (location = 2) in vec3 in_normal;

out vec3 worldPos;
out vec2 texCoord;
out vec3 normal;

uniform mat4 worldMatrix;
uniform mat4 projectedMatrix;

void main()
{
	worldPos = (worldMatrix * vec4(in_position, 1)).xyz;
	texCoord = in_texCoord;
	normal = mat3(worldMatrix) * in_normal;
	
	gl_Position = projectedMatrix * vec4(in_position, 1);
}*/

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