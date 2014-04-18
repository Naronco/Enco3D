#include "FontDatabase.h"

Font *Enco3D::Rendering::FontDatabase::LoadFont(const std::string &filename, const FontType &type)
{
	return new Font(filename, type);
}

Font *Enco3D::Rendering::FontDatabase::GetFont(const std::string &filename, const FontType &type)
{
	if (m_loadedFonts.find(filename) != m_loadedFonts.end())
	{
		return m_loadedFonts[filename];
	}

	Font *result = LoadFont(filename, type);
	m_loadedFonts.insert(std::pair<std::string, Font *>(filename, result));

	return result;
}