#include "BloomPostProcessEffect.h"

void Enco3D::Component::BloomPostProcessEffect::InitRendering()
{
	m_thresholdBuffer = new Rendering::Texture2D(GetWidth(), GetHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_horizontalBlurBuffer = new Rendering::Texture2D(GetWidth(), GetHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_verticalBlurBuffer = new Rendering::Texture2D(GetWidth(), GetHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);

	m_thresholdFramebuffer      = new Rendering::Framebuffer; m_thresholdFramebuffer->AttachTexture2D(m_thresholdBuffer,           Rendering::Attachment::Color0); m_thresholdFramebuffer->Pack();
	m_horizontalBlurFramebuffer = new Rendering::Framebuffer; m_horizontalBlurFramebuffer->AttachTexture2D(m_horizontalBlurBuffer, Rendering::Attachment::Color0); m_horizontalBlurFramebuffer->Pack();
	m_verticalBlurFramebuffer   = new Rendering::Framebuffer; m_verticalBlurFramebuffer->AttachTexture2D(m_verticalBlurBuffer,     Rendering::Attachment::Color0); m_verticalBlurFramebuffer->Pack();

	m_thresholdShader = Rendering::ShaderPool::GetInstance()->GetShader("shaders/threshold", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
	m_horizontalBlurShader = Rendering::ShaderPool::GetInstance()->GetShader("shaders/horizontalBlur", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
	m_verticalBlurShader = Rendering::ShaderPool::GetInstance()->GetShader("shaders/verticalBlur", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);

	m_generatedImageSlot = 0;
}

void Enco3D::Component::BloomPostProcessEffect::Deinit()
{
	delete m_thresholdBuffer;
	delete m_horizontalBlurBuffer;
	delete m_verticalBlurBuffer;

	delete m_thresholdFramebuffer;
	delete m_horizontalBlurFramebuffer;
	delete m_verticalBlurFramebuffer;
}

void Enco3D::Component::BloomPostProcessEffect::PostProcess(const Camera *camera)
{
	// GENERATE THE THRESHOLD TEXTURE //

	Rendering::BindFramebuffer(m_thresholdFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_thresholdShader->Bind();
	m_thresholdShader->SetUniformMatrix4x4f("matrix_worldViewProjectionMatrix", GetWorldViewProjectionMatrix());
	m_thresholdShader->SetUniformFloat("threshold", m_threshold);

	m_compositeBuffer->Bind(Rendering::TextureSampler::Sampler0); m_thresholdShader->SetUniformInt("thresholdTexture", Rendering::TextureSampler::Sampler0);
	
	RenderScreen();
	
	// BLUR THE THRESHOLD TEXTURE (HORIZONTAL) //

	Rendering::BindFramebuffer(m_horizontalBlurFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_horizontalBlurShader->Bind();
	m_horizontalBlurShader->SetUniformMatrix4x4f("matrix_worldViewProjectionMatrix", GetWorldViewProjectionMatrix());
	m_horizontalBlurShader->SetUniformInt("blurTexture", 0);
	m_horizontalBlurShader->SetUniformVector2f("postProcess_texelSize", GetTexelSize());
	m_horizontalBlurShader->SetUniformInt("blurSize", 8);

	m_thresholdBuffer->Bind(Rendering::TextureSampler::Sampler0); m_horizontalBlurShader->SetUniformInt("blurTexture", Rendering::TextureSampler::Sampler0);

	RenderScreen();
	
	// BLUR THE THRESHOLD TEXTURE (VERTICAL) //

	Rendering::BindFramebuffer(m_verticalBlurFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_verticalBlurShader->Bind();
	m_verticalBlurShader->SetUniformMatrix4x4f("matrix_worldViewProjectionMatrix", GetWorldViewProjectionMatrix());
	m_verticalBlurShader->SetUniformVector2f("postProcess_texelSize", GetTexelSize());
	m_verticalBlurShader->SetUniformInt("blurSize", 8);

	m_horizontalBlurBuffer->Bind(Rendering::TextureSampler::Sampler0); m_verticalBlurShader->SetUniformInt("blurTexture", Rendering::TextureSampler::Sampler0);
	
	RenderScreen();
	Rendering::BindFramebuffer(nullptr);
}

void Enco3D::Component::BloomPostProcessEffect::Resize(unsigned int width, unsigned int height)
{
	delete m_thresholdBuffer;
	delete m_horizontalBlurBuffer;
	delete m_verticalBlurBuffer;

	delete m_thresholdFramebuffer;
	delete m_horizontalBlurFramebuffer;
	delete m_verticalBlurFramebuffer;

	m_thresholdBuffer = new Rendering::Texture2D(width, height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_horizontalBlurBuffer = new Rendering::Texture2D(width, height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_verticalBlurBuffer = new Rendering::Texture2D(width, height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);

	m_thresholdFramebuffer = new Rendering::Framebuffer; m_thresholdFramebuffer->AttachTexture2D(m_thresholdBuffer, Rendering::Attachment::Color0); m_thresholdFramebuffer->Pack();
	m_horizontalBlurFramebuffer = new Rendering::Framebuffer; m_horizontalBlurFramebuffer->AttachTexture2D(m_horizontalBlurBuffer, Rendering::Attachment::Color0); m_horizontalBlurFramebuffer->Pack();
	m_verticalBlurFramebuffer = new Rendering::Framebuffer; m_verticalBlurFramebuffer->AttachTexture2D(m_verticalBlurBuffer, Rendering::Attachment::Color0); m_verticalBlurFramebuffer->Pack();
}