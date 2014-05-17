#include "SSAOPostProcessEffect.h"
#include "Random.h"
#include "Vector3.h"

void Enco3D::Component::SSAOPostProcessEffect::initRendering()
{
	m_ssaoBuffer = new Rendering::Texture2D(getWidth(), getHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_blurBuffer = new Rendering::Texture2D(getWidth(), getHeight(), GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	
	m_ssaoFramebuffer = new Rendering::Framebuffer; m_ssaoFramebuffer->attachTexture2D(m_ssaoBuffer, Rendering::Attachment::Color0); m_ssaoFramebuffer->pack();
	m_blurFramebuffer = new Rendering::Framebuffer; m_blurFramebuffer->attachTexture2D(m_blurBuffer, Rendering::Attachment::Color0); m_blurFramebuffer->pack();
	
	m_ssaoShader = Rendering::ShaderPool::getInstance()->getShader("shaders/ssao", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
	m_blurShader = Rendering::ShaderPool::getInstance()->getShader("shaders/ssaoBlur", Rendering::ShaderType::VertexShader | Rendering::ShaderType::FragmentShader);
	
	float randomValues[64];
	unsigned int pixelIndex = 0;
	for (unsigned int i = 0; i < 16; i++)
	{
		Core::Vector3f randomVec(Core::Random::nextFloat() * 2.0f - 1.0f, Core::Random::nextFloat() * 2.0f - 1.0f, 0.0f);
		randomVec = randomVec.normalize();

		randomVec.x = randomVec.x * 0.5f + 0.5f;
		randomVec.y = randomVec.y * 0.5f + 0.5f;
		randomVec.z = randomVec.z * 0.5f + 0.5f;

		randomValues[pixelIndex + 0] = randomVec.x;
		randomValues[pixelIndex + 1] = randomVec.y;
		randomValues[pixelIndex + 2] = randomVec.z;
		randomValues[pixelIndex + 3] = 1.0f;

		pixelIndex += 4;
	}

	m_randomTexture = new Rendering::Texture2D(4, 4, GL_RGBA, GL_RGBA, GL_NEAREST, GL_REPEAT, randomValues);

	m_generatedImageSlot = 1;
}

void Enco3D::Component::SSAOPostProcessEffect::deinit()
{
	delete m_randomTexture;

	delete m_ssaoBuffer;
	delete m_blurBuffer;

	delete m_ssaoFramebuffer;
	delete m_blurFramebuffer;
}

void Enco3D::Component::SSAOPostProcessEffect::postProcess(const Camera *camera)
{
	// GENERATE SSAO TEXTURE //

	Rendering::bindFramebuffer(m_ssaoFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_ssaoShader->bind();
	m_ssaoShader->setUniformMatrix4x4f("matrix_worldViewProjectionMatrix", getWorldViewProjectionMatrix());
	m_ssaoShader->setUniformMatrix4x4f("matrix_projectionMatrix", camera->getProjection());
	m_ssaoShader->setUniformFloat("ssaoRadius", m_ssaoRadius);
	m_ssaoShader->setUniformFloat("ssaoPower", m_ssaoPower);
	m_ssaoShader->setUniformFloat("ssaoStrength", m_ssaoStrength);
	m_ssaoShader->setUniformVector2f("postProcess_texelSize", getTexelSize());
	m_ssaoShader->setUniformFloat("camera_tanHalfFov", camera->getTanHalfFov());
	m_ssaoShader->setUniformFloat("camera_aspectRatio", camera->getAspectRatio());
	m_ssaoShader->setUniformFloat("camera_zNearClippingPlane", camera->getZNearClippingPlane());
	m_ssaoShader->setUniformFloat("camera_zFarClippingPlane", camera->getZFarClippingPlane());

	m_randomTexture->bind(Rendering::TextureSampler::Sampler2); m_ssaoShader->setUniformInt("randomTexture", Rendering::TextureSampler::Sampler2);
	m_depthBuffer->bind(Rendering::TextureSampler::Sampler1); m_ssaoShader->setUniformInt("gbuffer_depth", Rendering::TextureSampler::Sampler1);
	m_gbuffer1->bind(Rendering::TextureSampler::Sampler0); m_ssaoShader->setUniformInt("gbuffer_1", Rendering::TextureSampler::Sampler0);
	
	renderScreen();

	// BLUR THE SSAO TEXTURE //

	Rendering::bindFramebuffer(m_blurFramebuffer);
	glClear(GL_COLOR_BUFFER_BIT);

	m_blurShader->bind();
	m_blurShader->setUniformMatrix4x4f("matrix_worldViewProjectionMatrix", getWorldViewProjectionMatrix());
	m_blurShader->setUniformVector2f("texelSize", getTexelSize());
	m_blurShader->setUniformInt("blurSize", 4);

	m_ssaoBuffer->bind(Rendering::TextureSampler::Sampler0); m_blurShader->setUniformInt("inputTexture", Rendering::TextureSampler::Sampler0);

	renderScreen();
	Rendering::bindFramebuffer(nullptr);
}

void Enco3D::Component::SSAOPostProcessEffect::resize(unsigned int width, unsigned int height)
{
	delete m_ssaoBuffer;
	delete m_blurBuffer;
	
	delete m_ssaoFramebuffer;
	delete m_blurFramebuffer;
	
	m_ssaoBuffer = new Rendering::Texture2D(width, height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	m_blurBuffer = new Rendering::Texture2D(width, height, GL_RGBA, GL_RGBA, GL_NEAREST, GL_CLAMP_TO_EDGE);
	
	m_ssaoFramebuffer = new Rendering::Framebuffer; m_ssaoFramebuffer->attachTexture2D(m_ssaoBuffer, Rendering::Attachment::Color0); m_ssaoFramebuffer->pack();
	m_blurFramebuffer = new Rendering::Framebuffer; m_blurFramebuffer->attachTexture2D(m_blurBuffer, Rendering::Attachment::Color0); m_blurFramebuffer->pack();
}