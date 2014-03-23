#version 330

layout (location = 0) out vec3 out_worldPos;
layout (location = 1) out vec3 out_texCoord;
layout (location = 2) out vec3 out_normal;

in vec3 worldPos;
in vec2 texCoord;
in vec3 normal;

void main()
{
	out_worldPos = worldPos;
	out_texCoord = vec3(texCoord, 0);
	out_normal = normalize(normal) * 0.5f + 0.5f;
}