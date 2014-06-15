#ifndef _ENCO3D_FONTPOOL_H_
#define _ENCO3D_FONTPOOL_H_

#include "Font.h"
#include "TSingleton.h"
#include "DLLExport.h"

#include <map>

namespace Enco3D
{
	namespace Rendering
	{
		class DLL_EXPORT FontPool : public TSingleton < FontPool >
		{
		private:
			std::map<std::string, Font*> m_loadedFonts;
			Font *loadFont(const std::string &filename, const FontType &type);

		public:
			Font *getFont(const std::string &filename, const FontType &type);
			void release();
		};

		inline static Font *GetFont(const std::string &filename, const FontType &type)
		{
			return FontPool::getInstance()->getFont(filename, type);
		}
	}
}

#endif