#version 120

varying vec3 worldPos;
varying vec3 texCoord;
varying vec3 normal;

void main()
{
	gl_FragData[0] = vec4(worldPos, 1);
	gl_FragData[1] = vec4(texCoord, 1);
	gl_FragData[2] = vec4(normalize(normal) * 0.5f + 0.5f, 1);
}