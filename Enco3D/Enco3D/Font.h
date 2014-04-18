#ifndef _ENCO3D_FONT_H_
#define _ENCO3D_FONT_H_

#include "Texture.h"

#include <string>
#include <fstream>
#include <iostream>

using Enco3D::Rendering::Texture;

using std::string;
using std::ifstream;
using std::cout;
using std::cerr;
using std::endl;

namespace Enco3D
{
	namespace Rendering
	{
		struct CharacterData
		{
			float start_u, start_v, end_u, end_v;
			int offsX, offsY;
			unsigned int advanceX, width, height;
		};

		enum FontType : unsigned char
		{
			Default       = 0,
			Italic        = 1,
			Bold          = 2,
			BoldAndItalic = 3,
		};

		class Font
		{
		private:
			Texture *m_texture{ nullptr };
			CharacterData *m_characterData{ nullptr };
			unsigned int m_fontSize{ 0 };

		public:
			Font();
			Font(const string &name, const FontType &type);
			~Font();

			inline Texture *GetTexture() const { return m_texture; }
			inline CharacterData GetCharacterData(unsigned int index) { return m_characterData[index]; }
			inline unsigned int GetFontSize() const { return m_fontSize; }
		};
	}
}

#endif