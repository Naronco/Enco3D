#ifndef _ENCO3D_TEXTURECUBEMAP_H_
#define _ENCO3D_TEXTURECUBEMAP_H_

#include "ITexture.h"
#include "DebugLogger.h"

namespace Enco3D
{
	namespace Rendering
	{
		class TextureCubeMap : public ITexture
		{
		public:
			TextureCubeMap();
			TextureCubeMap(const std::string *filenames, unsigned int filter = GL_NEAREST, unsigned int wrap = GL_CLAMP);
			~TextureCubeMap();

			void Bind(unsigned int unit = 0) const;
		};
	}
}

#endif