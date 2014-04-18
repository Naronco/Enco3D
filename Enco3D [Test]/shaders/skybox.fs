#version 120

varying vec3 worldPos;

uniform samplerCube rendering_skybox;

void main()
{
	gl_FragColor = textureCube(rendering_skybox, normalize(worldPos));
}