#include "Font.h"

Enco3D::Rendering::Font::Font()
{
}

Enco3D::Rendering::Font::Font(const string &name)
{
	string textureFilename = name + string(".png");
	string dataFilename = name + string(".fnt");

	m_texture = new Texture(textureFilename, TextureTarget::Texture2D, TextureFilter::Linear, TextureWrap::Clamp);
	
	float iw = 1.0f / (float)m_texture->GetWidth();
	float ih = 1.0f / (float)m_texture->GetHeight();

	ifstream file;
	file.open(dataFilename.c_str());

	char temp;
	int numCharacters;

	if (!file.fail())
	{
#		define __findnextdef(streaminst) { streaminst.get(temp); while(temp != '=') { streaminst.get(temp); } }

		__findnextdef(file);

		file >> numCharacters;

		m_characterData = new CharacterData[256];

		unsigned int x, y, width, height;
		int offsx, offsy;
		unsigned int advancex;

		unsigned int fci = 0;

		for (unsigned int i = 0; i < numCharacters; i++)
		{
			__findnextdef(file); file >> fci;
			__findnextdef(file); file >> x;
			__findnextdef(file); file >> y;
			__findnextdef(file); file >> width;
			__findnextdef(file); file >> height;
			__findnextdef(file); file >> offsx;
			__findnextdef(file); file >> offsy;
			__findnextdef(file); file >> advancex;

			__findnextdef(file);
			__findnextdef(file);

			m_characterData[fci].start_u = x * iw;
			m_characterData[fci].start_v = y * ih;
			m_characterData[fci].end_u = m_characterData[fci].start_u+width * iw;
			m_characterData[fci].end_v = m_characterData[fci].start_v+height * ih;

			m_characterData[fci].width = width;
			m_characterData[fci].height = height;

			m_characterData[fci].offsX = offsx;
			m_characterData[fci].offsY = offsy;

			m_characterData[fci].advanceX = advancex;
		}
		
		cout << "Successfully loaded font data " << dataFilename << endl;
	}
	else
	{
		cerr << "[ERROR] Failed to load font data " << dataFilename << endl;
	}
}

Enco3D::Rendering::Font::~Font()
{
	if (m_characterData)
	{
		delete[] m_characterData;
		m_characterData = nullptr;
	}

	if (m_texture)
	{
		delete m_texture;
		m_texture = nullptr;
	}
}