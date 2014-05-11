#ifndef _ENCO3D_FONTPOOL_H_
#define _ENCO3D_FONTPOOL_H_

#include "Font.h"
#include "TSingleton.h"

#include <map>

namespace Enco3D
{
	namespace Rendering
	{
		class FontPool : public TSingleton<FontPool>
		{
		private:
			std::map<std::string, Font*> m_loadedFonts;
			Font *LoadFont(const std::string &filename, const FontType &type);

		public:
			Font *GetFont(const std::string &filename, const FontType &type);
			void Release();
		};

		inline static Font *GetFont(const std::string &filename, const FontType &type)
		{
			return FontPool::GetInstance()->GetFont(filename, type);
		}
	}
}

#endif