#include "TextureCubeMap.h"

Enco3D::Rendering::TextureCubeMap::TextureCubeMap()
{
}

Enco3D::Rendering::TextureCubeMap::TextureCubeMap(const std::string *filenames, unsigned int filter, unsigned int wrap)
{
	glGenTextures(1, &m_id);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, filter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, filter);

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, wrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, wrap);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, wrap);

	for (unsigned int i = 0; i < 6; i++)
	{
		int w, h, bytesPerPixel;
		unsigned char *data = stbi_load(filenames[i].c_str(), &w, &h, &bytesPerPixel, 4);

		glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

		if (data == nullptr)
		{
			Core::DebugLogger::log("[ERROR] Unable to load texture: " + filenames[i]);
			return;
		}
		else
			Core::DebugLogger::log("Successfully loaded texture " + filenames[i]);

		m_width = (unsigned int)w;
		m_height = (unsigned int)h;

		stbi_image_free(data);
	}

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	Core::DebugLogger::log("[OPEN_GL] Created texture cube map with id " + std::to_string(m_id));
}

Enco3D::Rendering::TextureCubeMap::~TextureCubeMap()
{
	Core::DebugLogger::log("[OPEN_GL] Released texture cube map with id " + std::to_string(m_id));

	glDeleteTextures(1, &m_id);
}

void Enco3D::Rendering::TextureCubeMap::bind(unsigned int unit) const
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_id);
}