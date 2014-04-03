#ifndef _ENCO3D_FONTTEXTUREBASE_H_
#define _ENCO3D_FONTTEXTUREBASE_H_

#include "Font.h"

#include <map>

using Enco3D::Rendering::Font;

namespace Enco3D
{
	namespace Rendering
	{
		class FontDatabase
		{
		private:
			std::map<std::string, Font *> m_loadedFonts;

		private:
			Font *LoadFont(const std::string &filename);

		public:
			Font *GetFont(const std::string &filename);

		public:
			inline static FontDatabase *GetInstance()
			{
				static FontDatabase *instance = nullptr;

				if (instance == nullptr)
				{
					instance = new FontDatabase;
				}

				return instance;
			}
		};
	}
}

#endif