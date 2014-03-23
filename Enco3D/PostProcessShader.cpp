#include "PostProcessShader.h"

Enco3D::Rendering::PostProcessShader::PostProcessShader()
{
	AddVertexShaderFromFile("shaders/postProcess.vs");
	AddFragmentShaderFromFile("shaders/postProcess.fs");

	SetAttribLocation("in_position", 0);
	SetAttribLocation("in_texCoord", 1);

	CompileShader();

	AddUniform("worldMatrix");
	AddUniform("projectedMatrix");

	AddUniform("gbuffer_position");
	AddUniform("gbuffer_texCoord");
	AddUniform("gbuffer_normal");
	AddUniform("gbuffer_depth");
}

void Enco3D::Rendering::PostProcessShader::UpdateUniforms(const Enco3D::Core::Matrix4x4f &worldMatrix, const Enco3D::Core::Matrix4x4f &projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	glClientActiveTexture(GL_TEXTURE3);
	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer->GetDepthTexture());
	SetUniformInt("gbuffer_depth", 3);

	glClientActiveTexture(GL_TEXTURE2);
	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer->GetTexture(2));
	SetUniformInt("gbuffer_normal", 2);

	glClientActiveTexture(GL_TEXTURE1);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer->GetTexture(1));
	SetUniformInt("gbuffer_texCoord", 1);

	glClientActiveTexture(GL_TEXTURE0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer->GetTexture(0));
	SetUniformInt("gbuffer_position", 0);
}