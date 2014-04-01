#include "SkyboxShader.h"

Enco3D::Rendering::SkyboxShader::SkyboxShader()
{
	AddVertexShaderFromFile("shaders/skybox.vs");
	AddFragmentShaderFromFile("shaders/skybox.fs");

	SetAttribLocation("in_position", 0);
	
	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

	AddUniform("eyePos");
	AddUniform("skyboxTexture");
}

void Enco3D::Rendering::SkyboxShader::UpdateUniforms(const Enco3D::Core::Matrix4x4f &worldMatrix, const Enco3D::Core::Matrix4x4f &projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	material.GetTexture("skybox")->Bind(0);

	SetUniformVector3f("eyePos", m_eyePos);
	SetUniformInt("skyboxTexture", 0);
}