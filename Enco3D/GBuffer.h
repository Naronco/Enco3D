#ifndef _ENCO3D_GBUFFER_H_
#define _ENCO3D_GBUFFER_H_

#include <GL\glew.h>

#include <iostream>

using std::cerr;
using std::endl;

namespace Enco3D
{
	namespace Rendering
	{
		enum GBufferTexture
		{
			Positions = 0,
			TexCoords = 1,
			Normals   = 2,
		};

		const int __numGBufferTextures = 1;

		class GBuffer
		{
		private:
			GLuint m_fbo;
			GLuint m_textures[__numGBufferTextures];
			GLuint m_depthTexture;
			
		public:
			GBuffer();
			GBuffer(unsigned int width, unsigned int height);
			~GBuffer();

			inline GLuint GetFBO() const { return m_fbo; }
			inline GLuint GetTexture(unsigned int index) const { return m_textures[index]; }
			inline GLuint GetDepthTexture() const { return m_depthTexture; }
		};
	}
}

#endif