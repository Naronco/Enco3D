#include "SSAOPostProcessEffect.h"

void Enco3D::Component::SSAOPostProcessEffect::InitRendering()
{
	m_ssaoBuffer = new Rendering::Texture2D(GetWidth(), GetHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_horizontalBlurBuffer = new Rendering::Texture2D(GetWidth(), GetHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_verticalBlurBuffer = new Rendering::Texture2D(GetWidth(), GetHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);

	m_ssaoFramebuffer = new Rendering::Framebuffer; m_ssaoFramebuffer->AttachTexture2D(m_ssaoBuffer, Rendering::Attachment::Color0); m_ssaoFramebuffer->Pack();
	m_horizontalBlurFramebuffer = new Rendering::Framebuffer; m_horizontalBlurFramebuffer->AttachTexture2D(m_horizontalBlurBuffer, Rendering::Attachment::Color0); m_horizontalBlurFramebuffer->Pack();
	m_verticalBlurFramebuffer = new Rendering::Framebuffer; m_verticalBlurFramebuffer->AttachTexture2D(m_verticalBlurBuffer, Rendering::Attachment::Color0); m_verticalBlurFramebuffer->Pack();

	m_ssaoShader = Rendering::ShaderPool::GetInstance()->GetShader("shaders/ssao", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
	m_horizontalBlurShader = Rendering::ShaderPool::GetInstance()->GetShader("shaders/horizontalBlur", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
	m_verticalBlurShader = Rendering::ShaderPool::GetInstance()->GetShader("shaders/verticalBlur", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);

	m_generatedImageSlot = 1;
}

void Enco3D::Component::SSAOPostProcessEffect::Deinit()
{
	delete m_ssaoBuffer;
	delete m_horizontalBlurBuffer;
	delete m_verticalBlurBuffer;

	delete m_ssaoFramebuffer;
	delete m_horizontalBlurFramebuffer;
	delete m_verticalBlurFramebuffer;
}

void Enco3D::Component::SSAOPostProcessEffect::PostProcess(const Camera *camera)
{
	// GENERATE SSAO TEXTURE //

	Rendering::BindFramebuffer(m_ssaoFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_ssaoShader->Bind();
	m_ssaoShader->SetUniformMatrix4x4f("matrix_worldViewProjectionMatrix", GetWorldViewProjectionMatrix());
	m_ssaoShader->SetUniformMatrix4x4f("matrix_projectionMatrix", camera->GetProjection());
	m_ssaoShader->SetUniformFloat("ssaoRadius", m_ssaoRadius);
	m_ssaoShader->SetUniformFloat("ssaoPower", m_ssaoPower);
	m_ssaoShader->SetUniformFloat("ssaoStrength", m_ssaoStrength);
	m_ssaoShader->SetUniformVector2f("postProcess_texelSize", GetTexelSize());
	m_ssaoShader->SetUniformFloat("camera_tanHalfFov", camera->GetTanHalfFov());
	m_ssaoShader->SetUniformFloat("camera_aspectRatio", camera->GetAspectRatio());
	m_ssaoShader->SetUniformFloat("camera_zNearClippingPlane", camera->GetZNearClippingPlane());
	m_ssaoShader->SetUniformFloat("camera_zFarClippingPlane", camera->GetZFarClippingPlane());

	m_depthBuffer->Bind(Rendering::TextureSampler::Sampler2); m_ssaoShader->SetUniformInt("gbuffer_depthTexture", Rendering::TextureSampler::Sampler2);
	m_compositeBuffer->Bind(Rendering::TextureSampler::Sampler1); m_ssaoShader->SetUniformInt("compositeTexture", Rendering::TextureSampler::Sampler1);
	m_normalBuffer->Bind(Rendering::TextureSampler::Sampler0); m_ssaoShader->SetUniformInt("gbuffer_normalTexture", Rendering::TextureSampler::Sampler0);

	RenderScreen();
	Rendering::BindFramebuffer(nullptr);

	// BLUR THE SSAO TEXTURE (HORIZONTAL) //

	Rendering::BindFramebuffer(m_horizontalBlurFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_horizontalBlurShader->Bind();
	m_horizontalBlurShader->SetUniformMatrix4x4f("matrix_worldViewProjectionMatrix", GetWorldViewProjectionMatrix());
	m_horizontalBlurShader->SetUniformInt("blurTexture", 0);
	m_horizontalBlurShader->SetUniformVector2f("postProcess_texelSize", GetTexelSize());
	m_horizontalBlurShader->SetUniformInt("blurSize", 4);

	m_ssaoBuffer->Bind(Rendering::TextureSampler::Sampler0); m_horizontalBlurShader->SetUniformInt("blurTexture", Rendering::TextureSampler::Sampler0);

	RenderScreen();

	// BLUR THE SSAO TEXTURE (VERTICAL) //

	Rendering::BindFramebuffer(m_verticalBlurFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_verticalBlurShader->Bind();
	m_verticalBlurShader->SetUniformMatrix4x4f("matrix_worldViewProjectionMatrix", GetWorldViewProjectionMatrix());
	m_verticalBlurShader->SetUniformVector2f("postProcess_texelSize", GetTexelSize());
	m_verticalBlurShader->SetUniformInt("blurSize", 4);

	m_horizontalBlurBuffer->Bind(Rendering::TextureSampler::Sampler0); m_verticalBlurShader->SetUniformInt("blurTexture", Rendering::TextureSampler::Sampler0);

	RenderScreen();
	Rendering::BindFramebuffer(nullptr);
}

void Enco3D::Component::SSAOPostProcessEffect::Resize(unsigned int width, unsigned int height)
{
	delete m_ssaoBuffer;
	delete m_horizontalBlurBuffer;
	delete m_verticalBlurBuffer;

	delete m_ssaoFramebuffer;
	delete m_horizontalBlurFramebuffer;
	delete m_verticalBlurFramebuffer;

	m_ssaoBuffer = new Rendering::Texture2D(width, height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_horizontalBlurBuffer = new Rendering::Texture2D(width, height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_verticalBlurBuffer = new Rendering::Texture2D(width, height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);

	m_ssaoFramebuffer = new Rendering::Framebuffer; m_ssaoFramebuffer->AttachTexture2D(m_ssaoBuffer, Rendering::Attachment::Color0); m_ssaoFramebuffer->Pack();
	m_horizontalBlurFramebuffer = new Rendering::Framebuffer; m_horizontalBlurFramebuffer->AttachTexture2D(m_horizontalBlurBuffer, Rendering::Attachment::Color0); m_horizontalBlurFramebuffer->Pack();
	m_verticalBlurFramebuffer = new Rendering::Framebuffer; m_verticalBlurFramebuffer->AttachTexture2D(m_verticalBlurBuffer, Rendering::Attachment::Color0); m_verticalBlurFramebuffer->Pack();
}