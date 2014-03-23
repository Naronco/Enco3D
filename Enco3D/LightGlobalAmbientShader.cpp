#include "LightGlobalAmbientShader.h"

Enco3D::Rendering::LightGlobalAmbientShader::LightGlobalAmbientShader()
{
	AddVertexShaderFromFile("shaders/lightGlobalAmbient.vs");
	AddFragmentShaderFromFile("shaders/lightGlobalAmbient.fs");

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);

	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

	AddUniform("globalAmbientLight");

	AddUniform("diffuseColor");
	AddUniform("diffuseTexture");

	m_globalAmbientLight = Vector3f(0.2f, 0.2f, 0.2f);
}

void Enco3D::Rendering::LightGlobalAmbientShader::UpdateUniforms(const Enco3D::Core::Matrix4x4f &worldMatrix, const Enco3D::Core::Matrix4x4f projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	material.GetTexture("diffuse").Bind(0);

	SetUniformVector3f("globalAmbientLight", m_globalAmbientLight);

	SetUniformVector3f("diffuseColor", material.GetVector3f("diffuse"));
	SetUniformInt("diffuseTexture", 0);
}