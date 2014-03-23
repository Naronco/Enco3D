#ifndef _ENCO3D_TEXTURE_H_
#define _ENCO3D_TEXTURE_H_

#include <GL/glew.h>
#include <iostream>
#include <assert.h>
#include <string>

#include "stb_image.h"

using namespace std;

namespace Enco3D
{
	namespace Rendering
	{
		enum TextureFilter
		{
			Nearest = GL_NEAREST,
			Linear = GL_LINEAR,
		};

		enum TextureWrap
		{
			Clamp = GL_CLAMP,
			Repeat = GL_REPEAT,
		};

		enum TextureTarget
		{
			Texture2D = GL_TEXTURE_2D,
		};

		class Texture
		{
		private:
			TextureTarget m_textureTarget;
			GLuint m_textureID{ 0 };

		private:
			void InitTexture(int width, int height, unsigned char *data, TextureTarget target, TextureFilter filter, TextureWrap wrap);

		private:
			static const Texture *s_lastBind;
			static Texture *s_blankTexture;

		public:
			Texture(const string &filename, TextureTarget target = TextureTarget::Texture2D, TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat);
			Texture(int width, int height, unsigned char *data, TextureTarget target = TextureTarget::Texture2D, TextureFilter filter = TextureFilter::Linear, TextureWrap wrap = TextureWrap::Repeat);

			void Bind(unsigned int unit = 0) const;
			void Release();

			inline GLuint GetTextureID() const { return m_textureID; }

		public:
			static Texture *GetBlankTexture();
		};
	}
}

#endif