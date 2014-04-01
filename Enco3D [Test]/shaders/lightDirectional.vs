#version 330

layout (location = 0) in vec3 in_position;
layout (location = 1) in vec3 in_texCoord;
layout (location = 2) in vec3 in_normal;

out vec3 texCoord;
out vec3 normal;
out vec3 worldPos;

uniform mat4 worldMatrix;
uniform mat4 projectedMatrix;

void main()
{
	texCoord = in_texCoord;
	normal = mat3(worldMatrix) * in_normal;
	worldPos = vec3(worldMatrix * vec4(in_position, 1));
	
	gl_Position = projectedMatrix * vec4(in_position, 1);
}