#version 120

attribute vec3 in_position;

varying vec3 worldPos;

uniform mat4 matrix_viewProjectionMatrix;
uniform vec3 camera_translation;

void main()
{
	worldPos = in_position;
	gl_Position = matrix_viewProjectionMatrix * vec4(in_position + camera_translation, 1.0f);
}