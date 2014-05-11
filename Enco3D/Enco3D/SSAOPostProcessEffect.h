#ifndef _ENCO3D_SSAOPOSTPROCESSEFFECT_H_
#define _ENCO3D_SSAOPOSTPROCESSEFFECT_H_

#include "IPostProcessEffect.h"

namespace Enco3D
{
	namespace Component
	{
		class SSAOPostProcessEffect : public IPostProcessEffect
		{
		private:
			Rendering::Framebuffer *m_ssaoFramebuffer, *m_horizontalBlurFramebuffer, *m_verticalBlurFramebuffer;
			Rendering::Texture2D *m_ssaoBuffer, *m_horizontalBlurBuffer, *m_verticalBlurBuffer;
			Rendering::Shader *m_ssaoShader, *m_horizontalBlurShader, *m_verticalBlurShader;

			float m_ssaoRadius{ 0.5f }, m_ssaoPower{ 1.0f }, m_ssaoStrength{ 1.0f };

		public:
			void InitRendering();
			void Deinit();

			void PostProcess(const Camera *camera);
			void Resize(unsigned int width, unsigned int height);

			inline void SetSSAORadius(float radius) { m_ssaoRadius = radius; }
			inline void SetSSAOPower(float power) { m_ssaoPower = power; }
			inline void SetSSAOStrength(float strength) { m_ssaoStrength = strength; }

			inline Rendering::Texture2D *GetFinalBuffer() { return m_verticalBlurBuffer; }
		};
	}
}

#endif