#include "GBuffer.h"

GBuffer::GBuffer()
{
}

GBuffer::GBuffer(unsigned int width, unsigned int height)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	glGenTextures(GBufferTextureType::NumTextures, m_textures);
	glGenTextures(1, &m_depthTexture);

	for (unsigned int i = 0; i < GBufferTextureType::NumTextures; i++)
	{
		glBindTexture(GL_TEXTURE_2D, m_textures[i]);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB32F, width, height, 0, GL_RGB, GL_FLOAT, nullptr);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, m_textures[i], 0);
	}

	glBindTexture(GL_TEXTURE_2D, m_depthTexture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT32F, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthTexture, 0);

	GLenum drawBuffers[] =
	{
		GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2
	};

	//glDrawBuffers(GBufferTextureType::NumTextures, drawBuffers);

	GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE)
	{
		cerr << "[ERROR] Failed to initialize deferred shading framebuffer" << endl;
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

GBuffer::~GBuffer()
{
}

void GBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);
}

void GBuffer::Debind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}