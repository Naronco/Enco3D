#include "Texture.h"

const Texture *Texture::s_lastBind = nullptr;
Texture *Texture::s_blankTexture = nullptr;

Texture::Texture(const string &filename, TextureTarget target, TextureFilter filter, TextureWrap wrap)
{
	int width, height, bytesPerPixel;
	unsigned char *data = stbi_load(filename.c_str(), &width, &height, &bytesPerPixel, 4);

	if (data == nullptr)
	{
		cout << "[ERROR] Unable to load texture: " << filename << endl;
		return;
	}
	else
	{
		cout << "Successfully loaded texture " << filename << endl;
	}

	InitTexture(width, height, data, target, filter, wrap);
	stbi_image_free(data);
}

Texture::Texture(int width, int height, unsigned char *data, TextureTarget target, TextureFilter filter, TextureWrap wrap)
{
	InitTexture(width, height, data, target, filter, wrap);
}

void Texture::InitTexture(int width, int height, unsigned char *data, TextureTarget target, TextureFilter filter, TextureWrap wrap)
{
	m_textureTarget = target;

	if (width > 0 && height > 0 && data != nullptr)
	{
		glGenTextures(1, &m_textureID);
		glBindTexture(target, m_textureID);

		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);

		glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap);
		glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap);

		glTexImage2D(target, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		m_textureID = 0;
	}
}

void Texture::Bind(unsigned int unit) const
{
	if (s_lastBind != this)
	{
		assert(unit >= 0 && unit <= 31);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(m_textureTarget, m_textureID);
	
		s_lastBind = this;
	}
}

void Texture::Release()
{
	glDeleteTextures(1, &m_textureID);
}

Texture *Texture::GetBlankTexture()
{
	if (s_blankTexture == nullptr)
	{
		unsigned char whitePixel[4] =
		{
			255, 255, 255, 255
		};

		s_blankTexture = new Texture(1, 1, whitePixel, TextureTarget::Texture2D, TextureFilter::Nearest, TextureWrap::Repeat);
	}

	return s_blankTexture;
}