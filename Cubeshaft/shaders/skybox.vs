#version 120

attribute vec3 in_position;

varying vec3 worldPos;

uniform mat4 matrix_rotationProjectionMatrix;

void main()
{
	worldPos = in_position;
	gl_Position = matrix_rotationProjectionMatrix * vec4(in_position, 1.0f);
}