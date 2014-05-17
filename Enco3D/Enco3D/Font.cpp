#include "Font.h"

Enco3D::Rendering::Font::Font()
{
}

Enco3D::Rendering::Font::Font(const std::string &name, const FontType &type)
{
	std::string textureFilename, dataFilename;

	switch (type)
	{
	case FontType::Default:
		textureFilename = name + std::string("/default.png");
		dataFilename = name + std::string("/default.fnt");
		break;

	case FontType::Italic:
		textureFilename = name + std::string("/italic.png");
		dataFilename = name + std::string("/italic.fnt");
		break;

	case FontType::Bold:
		textureFilename = name + std::string("/bold.png");
		dataFilename = name + std::string("/bold.fnt");
		break;

	case FontType::BoldAndItalic:
		textureFilename = name + std::string("/bold_and_italic.png");
		dataFilename = name + std::string("/bold_and_italic.fnt");
		break;
	}

	m_texture = new Texture2D(textureFilename, TextureFilter::Linear, TextureWrap::Clamp);
	
	float iw = 1.0f / (float)m_texture->getWidth();
	float ih = 1.0f / (float)m_texture->getHeight();

	std::ifstream file;
	file.open(dataFilename.c_str());

	char temp;
	unsigned int numCharacters;

	if (!file.fail())
	{
#		define FIND_NEXT_DEF(streaminst) { streaminst.get(temp); while(temp != '=') { streaminst.get(temp); } }

		FIND_NEXT_DEF(file);
		file >> m_fontSize;

		FIND_NEXT_DEF(file);
		file >> numCharacters;

		m_characterData = new CharacterData[256];

		unsigned int x, y, width, height;
		int offsX, offsY;
		unsigned int advanceX;

		unsigned int fci = 0;

		for (unsigned int i = 0; i < numCharacters; i++)
		{
			FIND_NEXT_DEF(file); file >> fci;
			FIND_NEXT_DEF(file); file >> x;
			FIND_NEXT_DEF(file); file >> y;
			FIND_NEXT_DEF(file); file >> width;
			FIND_NEXT_DEF(file); file >> height;
			FIND_NEXT_DEF(file); file >> offsX;
			FIND_NEXT_DEF(file); file >> offsY;
			FIND_NEXT_DEF(file); file >> advanceX;

			FIND_NEXT_DEF(file);
			FIND_NEXT_DEF(file);

			m_characterData[fci].startU = x * iw;
			m_characterData[fci].startV = y * ih;
			m_characterData[fci].endU = m_characterData[fci].startU + width * iw;
			m_characterData[fci].endV = m_characterData[fci].startV + height * ih;

			m_characterData[fci].width = width;
			m_characterData[fci].height = height;

			m_characterData[fci].offsX = offsX;
			m_characterData[fci].offsY = offsY;

			m_characterData[fci].advanceX = advanceX;
		}

		Core::DebugLogger::log("Successfully loaded font data " + dataFilename);
	}
	else
		Core::DebugLogger::log("[ERROR] Failed to load font data " + dataFilename);
}

Enco3D::Rendering::Font::~Font()
{
	if (m_characterData)
		delete[] m_characterData;
	if (m_texture)
		delete m_texture;
}