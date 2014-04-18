#version 120

attribute vec3 in_position;
attribute vec2 in_texCoord;
attribute vec3 in_normal;
attribute vec3 in_tangent;
attribute vec3 in_binormal;

varying vec2 texCoord;
varying vec3 worldPos;
varying mat3 tbnMatrix;

uniform mat4 worldMatrix;
uniform mat4 worldViewProjectionMatrix;

void main()
{
	texCoord = in_texCoord;
	worldPos = vec3(worldMatrix * vec4(in_position, 1.0f));
	tbnMatrix = transpose(mat3(in_tangent, in_binormal, in_normal));
	
	gl_Position = worldViewProjectionMatrix * vec4(in_position, 1.0f);
}