#include "FontDatabase.h"

Font *Enco3D::Rendering::FontDatabase::LoadFont(const std::string &filename)
{
	return new Font(filename);
}

Font *Enco3D::Rendering::FontDatabase::GetFont(const std::string &filename)
{
	if (m_loadedFonts.find(filename) != m_loadedFonts.end())
	{
		return m_loadedFonts[filename];
	}

	Font *result = LoadFont(filename);
	m_loadedFonts.insert(std::pair<std::string, Font *>(filename, result));

	return result;
}