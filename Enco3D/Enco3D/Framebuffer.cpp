#include "Framebuffer.h"

Enco3D::Rendering::Framebuffer::Framebuffer()
{
	glGenFramebuffers(1, &m_id);
	glBindFramebuffer(GL_FRAMEBUFFER, m_id);

	Core::DebugLogger::Log("[OPEN_GL] Created framebuffer with id " + std::to_string(m_id));
}

Enco3D::Rendering::Framebuffer::~Framebuffer()
{
	Core::DebugLogger::Log("[OPEN_GL] Released framebuffer with id " + std::to_string(m_id));

	glDeleteFramebuffers(1, &m_id);
}

void Enco3D::Rendering::Framebuffer::AttachTexture2D(Texture2D *texture, unsigned int attachment)
{
	if (attachment != Attachment::Depth)
	{
		unsigned int gl_attachment = GL_COLOR_ATTACHMENT0 + attachment;
		glFramebufferTexture2D(GL_FRAMEBUFFER, gl_attachment, GL_TEXTURE_2D, texture->GetID(), 0);
		m_attachments.push_back(gl_attachment);
	}
	else
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, texture->GetID(), 0);
}

void Enco3D::Rendering::Framebuffer::Pack()
{
	int numDrawBuffers = (int)m_attachments.size();
	GLenum *drawBuffers = new GLenum[numDrawBuffers];

	for (int i = 0; i < numDrawBuffers; i++)
		drawBuffers[i] = m_attachments[i];
	
	glDrawBuffers(numDrawBuffers, drawBuffers);

	delete[] drawBuffers;
}