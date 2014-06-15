#ifndef _ENCO3D_FRAMEBUFFER_H_
#define _ENCO3D_FRAMEBUFFER_H_

#include <GL/glew.h>
#include <vector>
#include "Texture2D.h"
#include "DebugLogger.h"
#include "DLLExport.h"

namespace Enco3D
{
	namespace Rendering
	{
		enum DLL_EXPORT Attachment : unsigned int
		{
			Color0,
			Color1,
			Color2,
			Color3,
			Color4,
			Color5,
			Color6,
			Color7,
			Color8,
			Color9,
			Depth,
		};

		class DLL_EXPORT Framebuffer
		{
		private:
			GLuint m_id;
			std::vector<unsigned int> m_attachments;

		public:
			Framebuffer();
			~Framebuffer();

			void attachTexture2D(Texture2D *texture, unsigned int attachment);
			void pack();

			inline GLuint getID() const { return m_id; }
		};

		inline static void bindFramebuffer(Framebuffer *framebuffer)
		{
			if (framebuffer != nullptr)
				glBindFramebuffer(GL_FRAMEBUFFER, framebuffer->getID());
			else
				glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}
	}
}

#endif