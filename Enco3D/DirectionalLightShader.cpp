#include "DirectionalLightShader.h"

DirectionalLightShader::DirectionalLightShader()
{
	AddVertexShaderFromFile("shaders/lightDirectional.vs");
	AddFragmentShaderFromFile("shaders/lightDirectional.fs");

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);
	SetAttribLocation("in_normal", 2);

	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

	AddUniform("directionalLight.color");
	AddUniform("directionalLight.intensity");
	AddUniform("directionalLight.direction");

	AddUniform("material.diffuseColor");
	AddUniform("material.diffuseTexture");
	AddUniform("material.specularIntensity");
	AddUniform("material.specularExponent");

	AddUniform("eyePos");
}

void DirectionalLightShader::UpdateUniforms(const Matrix4x4f &worldMatrix, const Matrix4x4f projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	SetUniformVector3f("directionalLight.color", m_color);
	SetUniformFloat("directionalLight.intensity", m_intensity);
	SetUniformVector3f("directionalLight.direction", m_direction);

	material.GetTexture("diffuse").Bind(0);

	SetUniformVector3f("material.diffuseColor", material.GetVector3f("diffuse"));
	SetUniformInt("material.diffuseTexture", 0);
	SetUniformFloat("material.specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformFloat("material.specularExponent", material.GetFloat("specularExponent"));

	SetUniformVector3f("eyePos", m_eyePos);
}