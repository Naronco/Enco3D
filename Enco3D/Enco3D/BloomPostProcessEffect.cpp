#include "BloomPostProcessEffect.h"

void Enco3D::Component::BloomPostProcessEffect::initRendering()
{
	m_thresholdBuffer = new Rendering::Texture2D(getWidth(), getHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_horizontalBlurBuffer = new Rendering::Texture2D(getWidth(), getHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_verticalBlurBuffer = new Rendering::Texture2D(getWidth(), getHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);

	m_thresholdFramebuffer      = new Rendering::Framebuffer; m_thresholdFramebuffer->attachTexture2D(m_thresholdBuffer,           Rendering::Attachment::Color0); m_thresholdFramebuffer->pack();
	m_horizontalBlurFramebuffer = new Rendering::Framebuffer; m_horizontalBlurFramebuffer->attachTexture2D(m_horizontalBlurBuffer, Rendering::Attachment::Color0); m_horizontalBlurFramebuffer->pack();
	m_verticalBlurFramebuffer   = new Rendering::Framebuffer; m_verticalBlurFramebuffer->attachTexture2D(m_verticalBlurBuffer,     Rendering::Attachment::Color0); m_verticalBlurFramebuffer->pack();

	m_thresholdShader = Rendering::ShaderPool::getInstance()->getShader("shaders/threshold", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
	m_horizontalBlurShader = Rendering::ShaderPool::getInstance()->getShader("shaders/horizontalBlur", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
	m_verticalBlurShader = Rendering::ShaderPool::getInstance()->getShader("shaders/verticalBlur", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);

	m_generatedImageSlot = 0;
}

void Enco3D::Component::BloomPostProcessEffect::deinit()
{
	delete m_thresholdBuffer;
	delete m_horizontalBlurBuffer;
	delete m_verticalBlurBuffer;

	delete m_thresholdFramebuffer;
	delete m_horizontalBlurFramebuffer;
	delete m_verticalBlurFramebuffer;
}

void Enco3D::Component::BloomPostProcessEffect::postProcess(const Camera *camera)
{
/*	// GENERATE THE THRESHOLD TEXTURE //

	Rendering::bindFramebuffer(m_thresholdFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_thresholdShader->bind();
	m_thresholdShader->setUniformMatrix4x4f("matrix_worldViewProjectionMatrix", getWorldViewProjectionMatrix());
	m_thresholdShader->setUniformFloat("threshold", m_threshold);

	m_compositeBuffer->bind(Rendering::TextureSampler::Sampler0); m_thresholdShader->setUniformInt("thresholdTexture", Rendering::TextureSampler::Sampler0);
	
	renderScreen();
	
	// BLUR THE THRESHOLD TEXTURE (HORIZONTAL) //

	Rendering::bindFramebuffer(m_horizontalBlurFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_horizontalBlurShader->bind();
	m_horizontalBlurShader->setUniformMatrix4x4f("matrix_worldViewProjectionMatrix", getWorldViewProjectionMatrix());
	m_horizontalBlurShader->setUniformInt("blurTexture", 0);
	m_horizontalBlurShader->setUniformVector2f("postProcess_texelSize", getTexelSize());
	m_horizontalBlurShader->setUniformInt("blurSize", 8);

	m_thresholdBuffer->bind(Rendering::TextureSampler::Sampler0); m_horizontalBlurShader->setUniformInt("blurTexture", Rendering::TextureSampler::Sampler0);

	renderScreen();
	
	// BLUR THE THRESHOLD TEXTURE (VERTICAL) //

	Rendering::bindFramebuffer(m_verticalBlurFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_verticalBlurShader->bind();
	m_verticalBlurShader->setUniformMatrix4x4f("matrix_worldViewProjectionMatrix", getWorldViewProjectionMatrix());
	m_verticalBlurShader->setUniformVector2f("postProcess_texelSize", getTexelSize());
	m_verticalBlurShader->setUniformInt("blurSize", 8);

	m_horizontalBlurBuffer->bind(Rendering::TextureSampler::Sampler0); m_verticalBlurShader->setUniformInt("blurTexture", Rendering::TextureSampler::Sampler0);
	
	renderScreen();
	Rendering::bindFramebuffer(nullptr);*/
}

void Enco3D::Component::BloomPostProcessEffect::resize(unsigned int width, unsigned int height)
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

	m_thresholdFramebuffer = new Rendering::Framebuffer; m_thresholdFramebuffer->attachTexture2D(m_thresholdBuffer, Rendering::Attachment::Color0); m_thresholdFramebuffer->pack();
	m_horizontalBlurFramebuffer = new Rendering::Framebuffer; m_horizontalBlurFramebuffer->attachTexture2D(m_horizontalBlurBuffer, Rendering::Attachment::Color0); m_horizontalBlurFramebuffer->pack();
	m_verticalBlurFramebuffer = new Rendering::Framebuffer; m_verticalBlurFramebuffer->attachTexture2D(m_verticalBlurBuffer, Rendering::Attachment::Color0); m_verticalBlurFramebuffer->pack();
}