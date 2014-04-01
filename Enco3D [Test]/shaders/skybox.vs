#version 330

layout (location = 0) in vec3 in_position;

out vec3 worldPos;

uniform mat4 worldMatrix;
uniform mat4 projectedMatrix;

uniform vec3 eyePos;

void main()
{
	worldPos = in_position;
	gl_Position = projectedMatrix * vec4(in_position + eyePos, 1);
}