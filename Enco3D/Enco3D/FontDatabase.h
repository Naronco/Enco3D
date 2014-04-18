#ifndef _ENCO3D_FONTTEXTUREBASE_H_
#define _ENCO3D_FONTTEXTUREBASE_H_

#include "Font.h"
#include "TSingleton.h"

#include <map>

using Enco3D::Rendering::Font;

namespace Enco3D
{
	namespace Rendering
	{
		class FontDatabase : public TSingleton<FontDatabase>
		{
		private:
			std::map<std::string, Font *> m_loadedFonts;
			Font *LoadFont(const std::string &filename, const FontType &type);

		public:
			Font *GetFont(const std::string &filename, const FontType &type);
		};

		inline static Font *GetFont(const std::string &filename, const FontType &type)
		{
			return FontDatabase::GetInstance()->GetFont(filename, type);
		}
	}
}

#endif