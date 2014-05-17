#ifndef _ENCO3D_TEXTURE2D_H_
#define _ENCO3D_TEXTURE2D_H_

#include "ITexture.h"
#include "DebugLogger.h"

namespace Enco3D
{
	namespace Rendering
	{
		class Texture2D : public ITexture
		{
		public:
			Texture2D();
			Texture2D(unsigned int width, unsigned int height, GLint internalFormat, GLenum format, unsigned int filter = GL_NEAREST, unsigned int wrap = GL_REPEAT, float *values = nullptr);
			Texture2D(const std::string &filename, unsigned int filter = GL_NEAREST, unsigned int wrap = GL_REPEAT);
			~Texture2D();

			void bind(unsigned int unit = 0) const;
		};
	}
}

#endif