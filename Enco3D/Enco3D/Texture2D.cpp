#include "Texture2D.h"

Enco3D::Rendering::Texture2D::Texture2D()
{
}

Enco3D::Rendering::Texture2D::Texture2D(unsigned int width, unsigned int height, GLint internalFormat, GLenum format, unsigned int filter, unsigned int wrap, float *values)
{
	m_width = width;
	m_height = height;

	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, (GLsizei)width, (GLsizei)height, 0, format, GL_FLOAT, values);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

	if (filter == TextureFilter::MipmapLinear)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	}

	glBindTexture(GL_TEXTURE_2D, 0);

	Core::DebugLogger::Log("Created texture 2d with id " + std::to_string(m_id));
}

Enco3D::Rendering::Texture2D::Texture2D(const std::string &filename, unsigned int filter, unsigned int wrap)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_2D, m_id);

	int width, height, bytesPerPixel;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &bytesPerPixel, 4);

	if (data == nullptr)
	{
		Core::DebugLogger::Log("[ERROR] Unable to load texture: " + filename);
		return;
	}
	else
		Core::DebugLogger::Log("Successfully loaded texture " + filename);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap);

	if (filter == TextureFilter::MipmapLinear)
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
	}

	m_width = (unsigned int)width;
	m_height = (unsigned int)height;

	stbi_image_free(data);

	glBindTexture(GL_TEXTURE_2D, 0);

	Core::DebugLogger::Log("[OPEN_GL] Created texture 2d with id " + std::to_string(m_id));
}

Enco3D::Rendering::Texture2D::~Texture2D()
{
	Core::DebugLogger::Log("[OPEN_GL] Released texture 2d with id " + std::to_string(m_id));
	
	glDeleteTextures(1, &m_id);
}

void Enco3D::Rendering::Texture2D::Bind(unsigned int unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D, m_id);
}