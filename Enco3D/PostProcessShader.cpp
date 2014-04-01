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
//	AddUniform("gbuffer_texCoord");
//	AddUniform("gbuffer_normal");
	AddUniform("gbuffer_depth");
}

void Enco3D::Rendering::PostProcessShader::UpdateUniforms(const Enco3D::Core::Matrix4x4f &worldMatrix, const Enco3D::Core::Matrix4x4f &projectedMatrix, Material &material) const
{
	SetUniformMatrix4x4f("worldMatrix", worldMatrix);
	SetUniformMatrix4x4f("projectedMatrix", projectedMatrix);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer->GetDepthTexture());
//	glActiveTexture(GL_TEXTURE2);
//	glBindTexture(GL_TEXTURE_2D, m_gbuffer->GetTexture(GBufferTexture::Normals));
//	glActiveTexture(GL_TEXTURE1);
//	glBindTexture(GL_TEXTURE_2D, m_gbuffer->GetTexture(GBufferTexture::TexCoords));
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_gbuffer->GetTexture(GBufferTexture::Positions));

	SetUniformInt("gbuffer_position", 0);
//	SetUniformInt("gbuffer_texCoord", 1);
//	SetUniformInt("gbuffer_normal", 2);
	SetUniformInt("gbuffer_depth", 3);
}