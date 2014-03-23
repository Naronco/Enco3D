#include "PointLightShader.h"

Enco3D::Rendering::PointLightShader::PointLightShader()
{
	AddVertexShaderFromFile("shaders/lightPoint.vs");
	AddFragmentShaderFromFile("shaders/lightPoint.fs");

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);
	SetAttribLocation("in_normal", 2);

	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

	AddUniform("pointLight.color");
	AddUniform("pointLight.intensity");
	AddUniform("pointLight.position");
	AddUniform("pointLight.range");

	AddUniform("material.diffuseColor");
	AddUniform("material.diffuseTexture");
	AddUniform("material.specularIntensity");
	AddUniform("material.specularExponent");

	AddUniform("eyePos");
}

void Enco3D::Rendering::PointLightShader::UpdateUniforms(const Enco3D::Core::Matrix4x4f &worldMatrix, const Enco3D::Core::Matrix4x4f projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	SetUniformVector3f("pointLight.color", m_color);
	SetUniformFloat("pointLight.intensity", m_intensity);
	SetUniformVector3f("pointLight.position", m_position);
	SetUniformFloat("pointLight.range", m_range);

	material.GetTexture("diffuse").Bind(0);

	SetUniformVector3f("material.diffuseColor", material.GetVector3f("diffuse"));
	SetUniformInt("material.diffuseTexture", 0);
	SetUniformFloat("material.specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformFloat("material.specularExponent", material.GetFloat("specularExponent"));

	SetUniformVector3f("eyePos", m_eyePos);
}