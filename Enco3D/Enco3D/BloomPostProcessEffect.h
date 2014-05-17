#ifndef _ENCO3D_BLOOMPOSTPROCESSEFFECT_H_
#define _ENCO3D_BLOOMPOSTPROCESSEFFECT_H_

#include "IPostProcessEffect.h"

namespace Enco3D
{
	namespace Component
	{
		class BloomPostProcessEffect : public IPostProcessEffect
		{
		private:
			Rendering::Framebuffer *m_thresholdFramebuffer, *m_horizontalBlurFramebuffer, *m_verticalBlurFramebuffer;
			Rendering::Texture2D *m_thresholdBuffer, *m_horizontalBlurBuffer, *m_verticalBlurBuffer;
			Rendering::Shader *m_thresholdShader, *m_horizontalBlurShader, *m_verticalBlurShader;

			float m_threshold{ 0.86f };

		public:
			void initRendering();
			void deinit();

			void postProcess(const Camera *camera);
			void resize(unsigned int width, unsigned int height);

			inline Rendering::Texture2D *getFinalBuffer() { return m_verticalBlurBuffer; }
			inline void setThreshold(float threshold) { m_threshold = threshold; }
			inline float getThreshold() const { return m_threshold; }
		};
	}
}

#endif