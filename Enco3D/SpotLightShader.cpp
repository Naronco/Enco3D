#include "SpotLightShader.h"

Enco3D::Rendering::SpotLightShader::SpotLightShader()
{
	AddVertexShaderFromFile("shaders/lightSpot.vs");
	AddFragmentShaderFromFile("shaders/lightSpot.fs");

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);
	SetAttribLocation("in_normal", 2);

	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

	AddUniform("spotLight.color");
	AddUniform("spotLight.intensity");
	AddUniform("spotLight.position");
	AddUniform("spotLight.direction");
	AddUniform("spotLight.range");
	AddUniform("spotLight.cutoff");

	AddUniform("material.diffuseColor");
	AddUniform("material.diffuseTexture");
	AddUniform("material.specularIntensity");
	AddUniform("material.specularExponent");

	AddUniform("eyePos");
}

void Enco3D::Rendering::SpotLightShader::UpdateUniforms(const Enco3D::Core::Matrix4x4f &worldMatrix, const Enco3D::Core::Matrix4x4f projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	SetUniformVector3f("spotLight.color", m_color);
	SetUniformFloat("spotLight.intensity", m_intensity);
	SetUniformVector3f("spotLight.position", m_position);
	SetUniformVector3f("spotLight.direction", m_direction);
	SetUniformFloat("spotLight.range", m_range);
	SetUniformFloat("spotLight.cutoff", m_cutoff);

	material.GetTexture("diffuse")->Bind(0);

	SetUniformVector3f("material.diffuseColor", material.GetVector3f("diffuse"));
	SetUniformInt("material.diffuseTexture", 0);
	SetUniformFloat("material.specularIntensity", material.GetFloat("specularIntensity"));
	SetUniformFloat("material.specularExponent", material.GetFloat("specularExponent"));

	SetUniformVector3f("eyePos", m_eyePos);
}