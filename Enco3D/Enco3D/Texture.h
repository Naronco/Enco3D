#ifndef _ENCO3D_TEXTURE_H_
#define _ENCO3D_TEXTURE_H_

#include "ReferenceCounter.h"

#include <GL/glew.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <map>

#include "stb_image.h"

using Enco3D::Core::ReferenceCounter;

using std::string;
using std::cout;
using std::cerr;
using std::endl;

namespace Enco3D
{
	namespace Rendering
	{
		enum TextureFilter
		{
			Nearest = GL_NEAREST,
			Linear = GL_LINEAR,
			MipMapLinear = 1,
		};

		enum TextureWrap
		{
			Clamp = GL_CLAMP,
			Repeat = GL_REPEAT,
		};

		enum TextureTarget
		{
			Texture2D = GL_TEXTURE_2D,
			TextureCubeMap = GL_TEXTURE_CUBE_MAP,
		};

		class TextureData : public ReferenceCounter<unsigned int>
		{
		private:
			GLenum m_textureTarget{ 0 };
			GLuint m_textureID{ 0 };
			unsigned int m_width{ 0 }, m_height{ 0 };

		public:
			TextureData(GLenum textureTarget, unsigned int width, unsigned int height);
			virtual ~TextureData();

			inline void SetWidth(unsigned int width) { m_width = width; }
			inline void SetHeight(unsigned int height) { m_height = height; }

			inline GLenum GetTextureTarget()
			{
				return m_textureTarget;
			}

			inline GLuint GetTextureID()
			{
				return m_textureID;
			}

			inline unsigned int GetWidth() const { return m_width; }
			inline unsigned int GetHeight() const { return m_height; }
		};

		class Texture
		{
		private:
			TextureData *m_textureData;
			string m_filename;

		private:
			void InitTexture(int width, int height, unsigned char *data, int bytesPerPixel, TextureTarget target, TextureFilter filter, TextureWrap wrap);

		private:
			static const Texture *s_lastBind;
			static Texture *s_blankTexture;

			static std::map<string, TextureData *> s_resourceMap;

		public:
			Texture();
			Texture(const string &filename, const TextureTarget &target = TextureTarget::Texture2D, const TextureFilter &filter = TextureFilter::Linear, const TextureWrap &wrap = TextureWrap::Repeat);
			Texture(int width, int height, unsigned char *data, const TextureTarget &target = TextureTarget::Texture2D, const TextureFilter &filter = TextureFilter::Linear, const TextureWrap &wrap = TextureWrap::Repeat);
			Texture(const string *filenames, const TextureFilter &filter = TextureFilter::Linear, const TextureWrap &wrap = TextureWrap::Repeat); // Cube Maps
			~Texture();
			
			void Bind(unsigned int unit = 0) const;
			
			inline GLuint GetTextureID() const { return m_textureData->GetTextureID(); }
			inline unsigned int GetWidth() const { return m_textureData->GetWidth(); }
			inline unsigned int GetHeight() const { return m_textureData->GetHeight(); }

		public:
			static Texture *GetBlankTexture();
		};
	}
}

#endif