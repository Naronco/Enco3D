#include "Texture.h"

const Enco3D::Rendering::Texture *Enco3D::Rendering::Texture::s_lastBind = nullptr;
Enco3D::Rendering::Texture *Enco3D::Rendering::Texture::s_blankTexture = nullptr;

std::map<string, Enco3D::Rendering::TextureData*> Enco3D::Rendering::Texture::s_resourceMap;

Enco3D::Rendering::TextureData::TextureData(GLenum textureTarget, unsigned int width, unsigned int height)
{
	glGenTextures(1, &m_textureID);
	m_textureTarget = textureTarget;
	m_width = width;
	m_height = height;
}

Enco3D::Rendering::TextureData::~TextureData()
{
	if (m_textureID) glDeleteTextures(1, &m_textureID);
}

Enco3D::Rendering::Texture::Texture()
{
}

Enco3D::Rendering::Texture::Texture(const string &filename, const TextureTarget &target, const TextureFilter &filter, const TextureWrap &wrap)
{
	m_filename = filename;

	std::map<string, TextureData*>::const_iterator it = s_resourceMap.find(filename);
	if (it != s_resourceMap.end())
	{
		m_textureData = it->second;
		m_textureData->AddReference();

		cout << "[INFO] Successfully copied available texture " << filename << endl;
	}
	else
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

		InitTexture(width, height, data, bytesPerPixel, target, filter, wrap);
		stbi_image_free(data);
	}
}

Enco3D::Rendering::Texture::~Texture()
{
	if (m_textureData && m_textureData->RemoveReference())
	{
		if (m_filename.length() > 0)
		{
			s_resourceMap.erase(m_filename);
		}

		delete m_textureData;
	}
}

Enco3D::Rendering::Texture::Texture(int width, int height, unsigned char *data, const TextureTarget &target, const TextureFilter &filter, const TextureWrap &wrap)
{
	InitTexture(width, height, data, 4, target, filter, wrap);
}

Enco3D::Rendering::Texture::Texture(const string *filenames, const TextureFilter &filter, const TextureWrap &wrap)
{
	m_textureData = new TextureData(GL_TEXTURE_CUBE_MAP, 0, 0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_textureData->GetTextureID());

	if (filter == TextureFilter::MipMapLinear)
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filter);
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrap);

	for (unsigned int i = 0; i < 6; i++)
	{
		int w, h, bytesPerPixel;
		unsigned char *data = stbi_load(filenames[i].c_str(), &w, &h, &bytesPerPixel, 4);

		GLint internalFormat;

		if (bytesPerPixel == 1)		 internalFormat = GL_R;
		else if (bytesPerPixel == 2) internalFormat = GL_RG;
		else if (bytesPerPixel == 3) internalFormat = GL_RGB;
		else if (bytesPerPixel == 4) internalFormat = GL_RGBA;
		
		GLenum format = (GLenum)internalFormat;

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		m_textureData->SetWidth((unsigned int)w);
		m_textureData->SetHeight((unsigned int)h);
		
		if (data == nullptr)
		{
			cout << "[ERROR] Unable to load texture: " << filenames[i] << endl;
			return;
		}
		else
		{
			cout << "Successfully loaded texture " << filenames[i] << endl;
		}

		stbi_image_free(data);
	}

	if (filter == TextureFilter::MipMapLinear)
	{
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
	}
}

void Enco3D::Rendering::Texture::InitTexture(int width, int height, unsigned char *data, int bytesPerPixel, TextureTarget target, TextureFilter filter, TextureWrap wrap)
{
	m_textureData = new TextureData(target, (unsigned int)width, (unsigned int)height);

	glBindTexture(target, m_textureData->GetTextureID());

	GLint internalFormat;

	if (bytesPerPixel == 1)		 internalFormat = GL_R;
	else if (bytesPerPixel == 2) internalFormat = GL_RG;
	else if (bytesPerPixel == 3) internalFormat = GL_RGB;
	else if (bytesPerPixel == 4) internalFormat = GL_RGBA;

	GLenum format = (GLenum)internalFormat;

	glTexImage2D(target, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);

	glTexParameteri(target, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(target, GL_TEXTURE_WRAP_T, wrap);

	if (filter == TextureFilter::MipMapLinear)
	{
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glGenerateMipmap(target);
	}
	else
	{
		glTexParameteri(target, GL_TEXTURE_MIN_FILTER, filter);
		glTexParameteri(target, GL_TEXTURE_MAG_FILTER, filter);
	}
}

void Enco3D::Rendering::Texture::Bind(unsigned int unit) const
{
	if (s_lastBind != this)
	{
		assert(unit >= 0 && unit <= 31);

		glActiveTexture(GL_TEXTURE0 + unit);
		glBindTexture(m_textureData->GetTextureTarget(), m_textureData->GetTextureID());
	
		s_lastBind = this;
	}
}

Enco3D::Rendering::Texture *Enco3D::Rendering::Texture::GetBlankTexture()
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